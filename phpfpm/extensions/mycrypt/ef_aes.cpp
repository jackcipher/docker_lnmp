#include "ef_aes.h"
#include "ef_md5.h"
#include "ef_hex.h"
#include "rijndael-api-fst.h"
#include <stdlib.h>
#include <string.h>

	int32 aes_encrypt(const std::string& src, 
		const std::string& key, std::string& dst){
		return aes_encrypt(src.data(), src.size(), key, dst);
	}

	int32 aes_encrypt(const char* src, size_t len,
                const std::string& key, std::string& dst){
                        int ret = 0;
                        keyInstance keyist;
                        u8 keymd5[16] = {0};
                        u8 keymat[33] = {0};
                        MD5(keymd5, (const u8*)key.data(), key.size());
                        bytes_to_hexs((const char*)keymd5, 16, (char*)keymat, 32);
                        ret = makeKey(&keyist, DIR_ENCRYPT, 128, keymat);
                        if(ret < 0){
                                return ret;
                        }

                        cipherInstance cnst;
                        ret = cipherInit(&cnst, MODE_ECB, (char*)keymat);
                        if(ret < 0){
                                return ret;
                        }

                        dst.resize(len + 16 - len % 16);
                        BYTE* encout = (BYTE*)dst.data();
                        if(len % 16){
                                ret = padEncrypt(&cnst, &keyist, (BYTE*)src, len, encout);
                        }else{
                                ret = blockEncrypt(&cnst, &keyist, (BYTE*)src, len, encout);
                        }
                        //std::cout << "enclen:" << ret << std::endl;
                        if(ret < 0)
                                return ret;
                        dst.resize(ret);
                        dst.append((char*)&len, sizeof(int));
                        return ret;
        }

int32 aes_decrypt(const char* src, size_t len,
                const std::string& key, std::string& dst){
                        int ret = 0;
                        keyInstance keyist;
                        u8 keymd5[16];
                        u8 keymat[33] = {0};
                        MD5(keymd5, (const u8*)key.data(), key.size());
                        bytes_to_hexs((const char*)keymd5, 16, (char*)keymat, 32);
                        ret = makeKey(&keyist, DIR_DECRYPT, 128, keymat);
                        if(ret < 0){
                                return ret;
                        }

                        cipherInstance cnst;
                        ret = cipherInit(&cnst, MODE_ECB, (char*)keymat);
                        if(ret < 0){
                                return ret;
                        }

                        int orglen = 0;
//                        orglen = *(src + len - sizeof(orglen));
						orglen = *(size_t*)(src + len - sizeof(orglen));
                        if(orglen > len - sizeof(orglen)){
                                return -10;
                        }

                       // std::cout << "declen:" << len << std::endl;
                        dst.resize(len + 16 - len % 16);
                        BYTE* encout = (BYTE*)dst.data();
                        if(orglen % 16){
                                ret = padDecrypt(&cnst, &keyist, (BYTE*)src, len - sizeof(orglen), encout);
                        }else{
                                ret = blockDecrypt(&cnst, &keyist, (BYTE*)src, len - sizeof(orglen), encout);

                        }
                        if(ret < 0)
                                return ret;
                        dst.resize(orglen);
                        return ret;
        }

	int32 aes_decrypt(const std::string& src, 
		const std::string& key, std::string& dst){
		return aes_decrypt(src.data(), src.size(), key, dst);
	}
	
