#include "UnitTest++.h"
#include "spark_protocol.h"

struct CoAPFixture
{
  static const uint8_t private_key[1192];
  static const uint8_t pubkey[294];
  static const uint8_t signed_encrypted_credentials[512];
  SparkProtocol spark_protocol;
  CoAPMessageType::Enum message_type;

  int init();
};

const uint8_t CoAPFixture::private_key[1192] =
  // padding
  "\x30\x82\x04\xa3\x02\x01\x00\x02\x82\x01\x01\x00"
  // modulus N
  "\xB9\x3F\xB4\x2D\x2A\x2C\xF5\xDA\x83\xD7\xE2\x26\x9F\xBE\x00\x47" \
  "\xFE\xFA\x62\xE8\xD5\x84\x1D\x2D\x3D\x08\x10\x25\xFE\xA8\x79\x59" \
  "\xA0\xAD\x78\x7C\x7A\x09\xBE\x76\x2B\x97\xEC\xF2\x05\xD4\x82\xF1" \
  "\xB0\xD8\x98\xC0\x60\x6F\x26\xAA\x5A\x50\xD0\x5D\x9F\xE1\x16\x01" \
  "\x28\x37\x20\x5B\x33\x40\x71\x43\xDC\x8B\xCB\x85\xF0\x1F\x20\x5C" \
  "\x2D\xC9\x7B\x40\xBD\xA2\x33\x25\xF7\x4A\x4E\xB0\xE3\x23\x67\x65" \
  "\xB2\xAB\x8B\x37\x9B\xF7\x29\x71\x97\x14\x6C\x68\xC5\x2B\x61\x20" \
  "\x40\x63\x6F\xD3\x9A\x0F\xE9\x8E\x91\x20\x24\x83\x90\x62\x2D\x0A" \
  "\x4E\xCB\x47\x7D\xCD\xD6\xA4\x85\x8E\xB2\x72\x80\x25\x38\xE5\xA5" \
  "\xCC\xCF\x1C\x2D\x63\x05\xE2\xD8\x5D\x34\xF4\x23\x43\xDB\x7D\x49" \
  "\x03\x89\xAA\x34\xD5\x01\x36\x31\x60\xFF\xA3\x80\x31\xFC\x8C\x75" \
  "\xD5\x7A\x98\x72\xCE\x70\x51\xC1\xB0\x37\x4E\x37\x48\x5B\x7D\x08" \
  "\x88\xE4\x98\xC0\xE1\xA0\x95\xB7\xB4\x5D\x2D\x13\x14\x15\xD3\x7F" \
  "\xAD\x8B\xED\x92\x49\x36\x4D\xDE\x93\xF6\xC0\x67\x44\x9C\xEF\x4B" \
  "\x32\xC7\x97\xF2\xB7\x60\x53\x19\x22\xB3\x3E\xD4\x1A\xD4\x5B\x7C" \
  "\xD7\x77\x2E\x37\x46\x0F\xB5\x82\x25\x0F\x6F\xB4\xD4\x67\x1C\xF7" \
  // padding
  "\x02\x03\x01\x00\x01\x02\x82\x01\x00"
  // private exponent D
  "\x2C\xC1\xC1\x6C\x70\x16\x30\xC8\x3C\xB6\x7A\x03\x4E\xF0\xFE\xEC" \
  "\x66\x24\x64\xA5\x50\x80\xFC\xF3\xA3\x1D\x41\x99\x8C\x6F\x73\xF2" \
  "\x3D\xA9\xEB\xC4\x57\x4F\xE7\x5E\x71\xA5\xE1\x2F\x90\x4D\x09\xDE" \
  "\x0F\x16\x25\xC1\xC5\x0A\xD5\xD2\xAE\xC3\x7B\xB4\x43\x1E\x84\xCC" \
  "\x7E\xC4\xE2\xE2\x65\xFD\x99\xE0\x05\x77\x19\x13\x21\x32\xC4\x04" \
  "\xC1\x63\x3E\x8E\x23\xC2\xFE\x8C\x9B\xB4\xAE\x52\x7A\x6E\x61\x5A" \
  "\xE6\xD2\x1F\x6E\xAE\x16\x07\x43\x54\x77\x30\xC2\x17\x71\x25\xA4" \
  "\x3F\x2A\x47\x28\x5E\xBE\x9D\x75\x3E\x86\xFF\x8B\x71\xE4\xE6\x70" \
  "\x7F\xB3\x63\x74\xBA\x70\x5A\x50\xA7\xFD\xDD\x7F\xA3\x85\x5D\x8B" \
  "\xF0\x0B\xBF\xB0\xFE\xE4\x0D\x28\x72\x0C\x87\x13\x60\xC3\xA7\xDC" \
  "\x09\xD5\x9C\x70\x84\xE2\x4C\x0F\xE8\xBB\x00\x2F\x66\x3F\x78\xC6" \
  "\x19\x12\x36\xDD\x67\x05\xF8\x94\x32\x01\xD9\xC8\xE8\x60\xD4\x64" \
  "\xC5\x5A\xF6\x34\x65\x1B\x96\xBB\xF3\x06\x6D\x2A\x08\xEE\xBB\xE8" \
  "\x95\x64\xDA\x3B\x13\xEB\xB9\x80\xE4\xCA\xB6\x33\x99\x7E\xEE\x33" \
  "\xC6\x9D\x65\xE3\xF7\x25\xD1\x91\xCF\x27\xE0\x25\x20\x0D\x8C\x66" \
  "\x57\x2C\xEB\x28\xA5\x3C\x5A\x5F\xC3\x85\x7C\xE6\xAB\x69\x38\xB1" \
  // padding
  "\x02\x81\x81\x00"
  // prime1 P
  "\xE6\xFE\xEE\x85\x98\xB9\xA4\x17\xF5\xAB\x2B\x97\x84\x4B\xF9\x27" \
  "\x0E\x41\x48\xE4\x77\x42\x9A\x0C\xE2\x9D\x0B\xD3\xE6\xF3\xBB\x4F" \
  "\xF5\x8C\x85\x53\x4E\x11\x9B\x40\xBF\xB9\x66\x25\x3E\x61\x57\x63" \
  "\xFF\x50\x53\x48\xF8\x6D\x00\x7D\x3E\xC5\x0D\xFA\x6B\xFF\x07\xBF" \
  "\x9C\xC0\xFC\x7A\x0B\x76\x6C\xB5\x9F\x6E\xBD\x4F\x3E\x82\x87\xD9" \
  "\xEF\x5B\x94\xE8\x25\xD8\x19\x5A\x20\xF1\x57\x47\x2C\xCB\xC8\x95" \
  "\xE6\xC7\xAF\x5C\xD4\xB0\x7C\x3D\xCC\x95\x7E\x7C\x73\x5B\x30\x76" \
  "\x80\x19\x37\xAD\x83\xE8\xAC\xA2\xA1\xFC\xCF\x51\x33\xE9\xD2\x9D" \
  // padding
  "\x02\x81\x81\x00"
  // prime2 Q
  "\xCD\x4D\x16\xB6\x57\x80\x31\xDA\x4E\x00\x6E\x1B\x79\xD0\xCE\x98" \
  "\x96\x44\xE1\x77\xD4\x8F\xB5\x5E\x8D\xB0\x1B\xCA\x24\xB0\x84\xC4" \
  "\x49\xC0\x1F\x61\xBF\x8A\xCC\xDC\xD3\xED\xEA\xAA\xBF\xA1\x0B\x23" \
  "\x34\x07\xAC\x17\xEC\x87\x51\x3B\x7A\x0B\xFA\x27\x8C\x8F\xBA\xD0" \
  "\x06\x2C\x69\xAE\x9C\xBC\xB5\x07\x3A\x1C\x72\x68\xB6\x19\xBB\x9A" \
  "\x99\x34\xC8\x49\xAD\xD0\xC7\x70\x97\x2D\xB7\x88\xAB\xBE\x45\xAC" \
  "\x95\xDE\x03\x45\xC6\x12\xCE\x7C\xE7\xB2\x15\xE2\xCA\x62\x7E\x5A" \
  "\xE7\xCA\x0E\x1E\x23\xB9\x8D\x93\x75\xEC\xA0\x20\xC0\x89\x1F\xA3" \
  // padding
  "\x02\x81\x80"
  // exponent1 DP
  "\x14\xA3\x0B\xEE\x35\x91\xC8\x3E\x37\xBD\x7E\x1C\x80\x3E\x45\x59" \
  "\x1E\xE5\xE8\x3C\x39\x07\x63\x39\xE9\x78\xFC\x58\x87\x16\x99\x52" \
  "\x70\x6E\x88\x6E\xC3\xD7\xC0\xD6\x0D\x0A\xE4\x3C\x49\x91\x6A\xBC" \
  "\x4D\x50\x00\xD0\xD1\x18\xF3\xE5\x3C\x99\x60\x41\x52\x2A\xAB\xA7" \
  "\x8B\xBA\x96\x13\xD5\x38\x54\x47\xF9\xA1\x6C\x1A\x4B\x4C\x60\x14" \
  "\xB1\x54\xAE\x3D\xFB\x3B\x8E\x30\x46\x27\x29\x93\xFB\x45\x8D\x7B" \
  "\x0E\xEE\x22\x15\x9A\x0E\xD6\x5A\xB3\x0F\x5C\x08\x84\x49\xCE\x4F" \
  "\x97\xEC\x28\xD4\x40\xA7\xA5\xDC\xB5\xBA\x1F\x4F\x72\xE2\xDD\xE5" \
  // padding
  "\x02\x81\x80"
  // exponent2 DQ
  "\x6C\xEF\xA5\xC8\x95\x7F\x81\x74\x7C\x05\x40\x67\xB5\xE8\xB5\x67" \
  "\x43\xFD\x42\xC2\x49\xF9\x03\x5D\x2B\xC3\xB1\xCB\x3E\x52\xA7\xF0" \
  "\x5B\xCD\xE5\x19\x02\x01\x0D\x99\x73\x9E\xFF\xF1\x20\x83\xBC\x9C" \
  "\x2E\x64\x8F\xCD\x96\x05\x6B\x76\x2A\xD9\xA6\x20\x4C\x36\x8C\x03" \
  "\x0B\xF3\x8F\x14\x47\x38\xDE\xB9\xF9\xFC\xD4\x3C\x79\xBC\x07\xCF" \
  "\x0D\xD2\x73\x20\x9D\x69\x76\x1A\x69\x2D\xAA\x00\x8C\x59\x07\x31" \
  "\x7F\xC8\x71\x66\x19\xA7\x2B\x08\x1E\x0D\x62\x0D\x98\x24\x51\x35" \
  "\xBD\x5E\x7A\xC5\x45\x61\x95\x1D\x14\xEA\xBD\x41\x03\xC8\xFF\x0F" \
  // padding
  "\x02\x81\x81\x00"
  // coefficient QP
  "\xA5\x1B\x7A\x54\xBF\xB6\xA8\xD1\xB9\xA5\x60\x62\x78\x32\xDA\xDC" \
  "\x57\x00\xF2\x18\xD6\xEA\xFD\x8F\xE4\x02\xAD\xC5\x18\x21\x09\x55" \
  "\x9B\xF9\x91\x4B\x06\x70\x78\x84\x9C\x6E\xF5\x49\xE5\xE8\x76\x19" \
  "\xDD\x59\xC6\xFD\x79\xC5\x05\x55\x7D\xFF\xF6\xA0\x55\x8F\xF2\xF4" \
  "\x31\x02\x6D\x8D\x04\x5F\xF2\x00\x84\x48\x0F\xE0\x15\xB0\x9E\xE2" \
  "\x18\x2D\xCC\x52\x01\x0E\xC7\xB7\xC0\xAA\x12\x3E\xEF\xD0\x3D\x79" \
  "\xF3\xDD\x2D\x49\xB1\x17\x2D\xA8\x22\x68\xCB\xCE\x0F\x45\xF7\x08" \
  "\x10\x44\x52\xD1\x94\x35\x86\x36\x33\x2B\x4B\x36\xF1\x56\x42\xA3";

const uint8_t CoAPFixture::pubkey[294] = {
  0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09,
  0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01,
  0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00,
  0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01,
  0x00, 0xb5, 0x46, 0xfd, 0x64, 0xb8, 0x56, 0xb0,
  0xd0, 0x2f, 0xdc, 0x9f, 0x33, 0x6b, 0x65, 0x4c,
  0x7e, 0x65, 0x8d, 0x8f, 0x95, 0x57, 0x76, 0xcf,
  0x34, 0xa7, 0xe6, 0xb2, 0xc2, 0x0e, 0xad, 0xd9,
  0x22, 0x31, 0xd5, 0x36, 0x6c, 0x1b, 0x10, 0x4f,
  0xd4, 0x47, 0xc9, 0x79, 0x54, 0xcf, 0xd5, 0xb7,
  0xa5, 0xfa, 0x64, 0xb6, 0x28, 0xf2, 0xda, 0x96,
  0xba, 0xe4, 0x91, 0x0d, 0xdd, 0x85, 0x39, 0x79,
  0x83, 0x97, 0xfb, 0x24, 0x43, 0x11, 0x1f, 0x23,
  0x43, 0xbe, 0xfa, 0x65, 0x4e, 0xab, 0x87, 0x70,
  0x3f, 0x3a, 0x8b, 0x56, 0xd1, 0xdd, 0x91, 0x3f,
  0x7d, 0x4e, 0xb2, 0x7d, 0xfb, 0x75, 0x0d, 0x83,
  0x79, 0x67, 0x87, 0xa5, 0xc8, 0x06, 0xe0, 0x10,
  0xd8, 0xc6, 0x9a, 0xb0, 0x7a, 0x39, 0x81, 0xb0,
  0xb2, 0x2d, 0x2d, 0x99, 0x8c, 0xa6, 0xfe, 0x2e,
  0xd1, 0x90, 0xe9, 0x33, 0x05, 0x65, 0xb6, 0xb0,
  0x50, 0xc1, 0x32, 0x2d, 0x0a, 0x91, 0x58, 0xd5,
  0x81, 0x18, 0x9e, 0xeb, 0x9e, 0x6e, 0x0a, 0x83,
  0x4c, 0x23, 0x68, 0x77, 0x0a, 0x8c, 0x50, 0x7c,
  0xd8, 0x6f, 0xa3, 0x57, 0x0e, 0xf8, 0x39, 0x96,
  0x9a, 0x35, 0x4e, 0x85, 0x4b, 0xf0, 0x6c, 0xac,
  0xdf, 0xaf, 0x90, 0x7c, 0xe9, 0x73, 0x2b, 0xca,
  0x3d, 0x80, 0x2f, 0x50, 0xa1, 0xc6, 0x72, 0x6b,
  0xb9, 0x66, 0x2e, 0x09, 0x22, 0x2b, 0x07, 0x7c,
  0x79, 0xed, 0x34, 0x3d, 0x47, 0x43, 0x6c, 0x5f,
  0x6c, 0xcc, 0xfc, 0xb6, 0xd5, 0x43, 0xc1, 0x3c,
  0x16, 0x03, 0x2d, 0xc9, 0x3d, 0x6a, 0x52, 0xc7,
  0xc3, 0xc4, 0x36, 0xf4, 0xb0, 0xc8, 0xde, 0xd8,
  0x3c, 0xa3, 0x9e, 0x60, 0xeb, 0x0a, 0x87, 0x37,
  0xc9, 0x6d, 0xf7, 0x99, 0x60, 0x17, 0x5a, 0xfe,
  0x59, 0x65, 0xa2, 0x7f, 0x18, 0xfa, 0xa7, 0x2a,
  0x26, 0x84, 0x77, 0x8b, 0xa8, 0xe5, 0xc7, 0x70,
  0x19, 0x02, 0x03, 0x01, 0x00, 0x01 };

const uint8_t CoAPFixture::signed_encrypted_credentials[512] = {
  0xa0, 0xd1, 0xf4, 0x84, 0x09, 0x97, 0xaa, 0x3b,
  0x13, 0xaa, 0x38, 0xb3, 0x85, 0x19, 0xf8, 0xdc,
  0x71, 0x6a, 0xe3, 0xbd, 0xb2, 0x4b, 0x59, 0x4c,
  0x01, 0x42, 0x95, 0x35, 0x83, 0x10, 0xd6, 0x87,
  0x0a, 0xa2, 0x8e, 0x31, 0xb0, 0x1f, 0x4d, 0x9c,
  0xeb, 0x95, 0xc1, 0x48, 0xf7, 0xe5, 0x03, 0xc7,
  0x5f, 0xf5, 0xcc, 0x4b, 0x97, 0x9e, 0xa5, 0xf2,
  0x6e, 0x1d, 0x66, 0x24, 0xdb, 0xff, 0x4a, 0x2c,
  0x32, 0xd7, 0x12, 0xe7, 0x76, 0xaa, 0x8b, 0xed,
  0x73, 0x20, 0xd9, 0x09, 0xe6, 0x76, 0xb6, 0xb4,
  0xb6, 0x87, 0x03, 0x6e, 0xb2, 0x11, 0x81, 0x4d,
  0x3a, 0xbc, 0x3e, 0x0f, 0x7a, 0x4c, 0x17, 0xfe,
  0x04, 0xa4, 0x24, 0x8f, 0x9c, 0xfe, 0x5a, 0x2a,
  0x50, 0x80, 0x38, 0x28, 0xab, 0x61, 0x79, 0x41,
  0xa8, 0x13, 0x5e, 0x0b, 0xa2, 0x92, 0x01, 0xe7,
  0x6e, 0x04, 0xc4, 0xd1, 0xcf, 0xf2, 0x00, 0x36,
  0x37, 0x6b, 0x81, 0xa8, 0x2e, 0x20, 0x88, 0x18,
  0x98, 0x76, 0x5a, 0xa7, 0xd4, 0xf5, 0x15, 0x1d,
  0x8a, 0xe3, 0x4b, 0xbb, 0x55, 0x7b, 0x11, 0x5c,
  0x6b, 0x59, 0x7a, 0x84, 0x85, 0x0e, 0xd0, 0x77,
  0xb6, 0x0b, 0xa4, 0x89, 0xd0, 0x7b, 0x71, 0xe8,
  0x66, 0xd4, 0x57, 0xce, 0x38, 0xf2, 0xed, 0x3b,
  0x64, 0x1b, 0x75, 0xb2, 0x91, 0x80, 0x26, 0x91,
  0xf9, 0xd1, 0x93, 0x00, 0x2b, 0xd7, 0x59, 0x46,
  0xfe, 0xbe, 0xa9, 0x5a, 0x79, 0x9f, 0x41, 0x06,
  0xb9, 0x93, 0x09, 0x5e, 0x49, 0x0e, 0x08, 0xf3,
  0x91, 0xfb, 0x32, 0x0a, 0xd4, 0xbb, 0x5f, 0x4c,
  0x61, 0xab, 0xa2, 0x24, 0x45, 0x23, 0x42, 0x30,
  0x94, 0x5f, 0xed, 0x27, 0x21, 0x7b, 0x89, 0xce,
  0xda, 0x15, 0xd5, 0x29, 0x23, 0x93, 0xcd, 0xf8,
  0x48, 0x6b, 0x80, 0x95, 0xc7, 0x9a, 0x76, 0xa7,
  0x53, 0x8d, 0x64, 0x6d, 0xd5, 0x60, 0x8e, 0x25,
  // signature
  0x5e, 0x57, 0x0c, 0x34, 0xea, 0xa8, 0xde, 0x40,
  0x2d, 0x59, 0x4e, 0x97, 0x56, 0x26, 0xea, 0xf4,
  0xcb, 0x42, 0x8b, 0x01, 0x05, 0x29, 0xe1, 0x8b,
  0x1c, 0x53, 0xe1, 0x15, 0xd7, 0x4a, 0x3c, 0xe8,
  0x47, 0xfd, 0x01, 0x59, 0xfa, 0x5f, 0x00, 0xf8,
  0xeb, 0x89, 0x47, 0x84, 0xe2, 0x98, 0x4c, 0x95,
  0xe7, 0xda, 0x7f, 0x12, 0xb7, 0xc2, 0x3f, 0x66,
  0xc3, 0xd5, 0x63, 0xfc, 0xb2, 0xb9, 0xc9, 0xfe,
  0x09, 0xd8, 0x27, 0xe5, 0xe0, 0x81, 0x39, 0xec,
  0xd5, 0x58, 0x9e, 0x76, 0x4c, 0x87, 0x06, 0x8b,
  0x18, 0x7a, 0x3e, 0xf5, 0x2d, 0xaa, 0x90, 0xb3,
  0x84, 0xf5, 0x3a, 0xa4, 0x48, 0x5d, 0x38, 0x2a,
  0x17, 0x4b, 0x34, 0x1f, 0xf0, 0x79, 0xfc, 0xb0,
  0xd9, 0xed, 0x36, 0xe9, 0x7c, 0x73, 0x14, 0xac,
  0xa4, 0x82, 0x3d, 0x8c, 0xdb, 0x5c, 0x14, 0x32,
  0xfa, 0x50, 0x0c, 0x89, 0x76, 0xd6, 0x39, 0x6f,
  0x66, 0x8b, 0xb0, 0x1c, 0x6f, 0xf3, 0x3b, 0x6e,
  0x15, 0x89, 0xfb, 0x94, 0xfe, 0xd1, 0x22, 0xdf,
  0x18, 0xd5, 0x03, 0xf7, 0x1b, 0xff, 0x19, 0x1e,
  0xba, 0xdc, 0xf5, 0x14, 0xa4, 0x6f, 0xd3, 0x8f,
  0xb8, 0x30, 0x06, 0x50, 0xdb, 0xa5, 0xf2, 0x2d,
  0xf8, 0x2f, 0xd9, 0x71, 0xdd, 0x69, 0xc0, 0x98,
  0xd5, 0xf6, 0xd8, 0x29, 0xfc, 0xc9, 0xc7, 0x64,
  0x11, 0xde, 0xa2, 0xb2, 0xfe, 0x34, 0xc2, 0xa2,
  0x53, 0xa6, 0x14, 0xa6, 0x0b, 0x10, 0x27, 0x66,
  0x81, 0x65, 0x37, 0x31, 0xf9, 0xac, 0x53, 0xa1,
  0xcb, 0x29, 0xde, 0xcc, 0x9b, 0x23, 0x28, 0x99,
  0x14, 0xdb, 0xf9, 0x7c, 0xbc, 0xab, 0xd5, 0x39,
  0x9d, 0xfa, 0x3d, 0x4f, 0x52, 0x44, 0x1b, 0x28,
  0x4e, 0x2e, 0xee, 0x3d, 0xfb, 0x31, 0x56, 0x5b,
  0x66, 0x0d, 0x9f, 0x3c, 0xeb, 0xa0, 0x7e, 0x9e,
  0x46, 0x98, 0xb6, 0x26, 0xe2, 0x89, 0xa1, 0xac };

int CoAPFixture::init()
{
  return spark_protocol.init(private_key, pubkey, signed_encrypted_credentials);
}


SUITE(CoAP)
{
  TEST_FIXTURE(CoAPFixture, SparkProtocolInitSucceeds)
  {
    CHECK_EQUAL(0, init());
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageReturnsCoAPMessageTypeFunction)
  {
    uint8_t ciphertext[32] = {
      0x43, 0x52, 0x3e, 0x02, 0x6c, 0x86, 0x75, 0xb7,
      0x73, 0xcf, 0x8b, 0x50, 0x16, 0xa6, 0x5b, 0x5b,
      0xea, 0x48, 0x63, 0xd9, 0xf0, 0x30, 0xd3, 0xce,
      0xba, 0x39, 0xff, 0x46, 0x30, 0x9b, 0x24, 0xfc };
    init();
    message_type = spark_protocol.received_message(ciphertext, 32);
    CHECK_EQUAL(CoAPMessageType::FUNCTION_CALL, message_type);
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageReturnsCoAPMessageTypeVariable)
  {
    uint8_t ciphertext[32] = {
      0x28, 0x40, 0x39, 0x27, 0x2a, 0x1b, 0x3f, 0xb3,
      0xfa, 0x1c, 0xb3, 0x83, 0x66, 0x25, 0xc5, 0xba,
      0xf8, 0x73, 0x98, 0xc3, 0xe6, 0x8e, 0x7c, 0x34,
      0xea, 0xb8, 0x8c, 0xec, 0x2b, 0xd5, 0x25, 0xb0 };
    init();
    message_type = spark_protocol.received_message(ciphertext, 32);
    CHECK_EQUAL(CoAPMessageType::VARIABLE_REQUEST, message_type);
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageRecognizesKeyChange)
  {
    uint8_t ciphertext[528] = {
      0xA5, 0x8C, 0x0B, 0x2B, 0xAE, 0xAC, 0x2A, 0xB4,
      0x10, 0xFE, 0x8C, 0xFB, 0x77, 0xC4, 0x92, 0x7B,
      0x8E, 0xB4, 0x4D, 0x59, 0x16, 0xDA, 0x41, 0x54,
      0x35, 0x7C, 0xAC, 0x15, 0x7A, 0x06, 0xB3, 0x39,
      0x30, 0x96, 0xB3, 0x45, 0x70, 0x90, 0xFE, 0x92,
      0xAA, 0x83, 0x1A, 0xD9, 0x94, 0x30, 0xF8, 0x72,
      0x0C, 0xE3, 0x1A, 0x2D, 0x6B, 0x85, 0xC3, 0x70,
      0x15, 0xA7, 0x09, 0xDF, 0x5F, 0xF0, 0xA4, 0xA3,
      0x9D, 0x93, 0x6D, 0x6E, 0xD7, 0x0E, 0x7F, 0x21,
      0x44, 0xEF, 0x71, 0xC9, 0xC5, 0xEA, 0x5A, 0x86,
      0x70, 0x5F, 0x17, 0xCC, 0x66, 0x23, 0xD5, 0xAC,
      0x85, 0xA0, 0x42, 0xE4, 0x8A, 0xF1, 0x68, 0x4B,
      0x62, 0x0F, 0x99, 0x88, 0x1A, 0x07, 0x59, 0x1A,
      0x7D, 0x21, 0x53, 0x86, 0x3A, 0xD6, 0x64, 0x91,
      0xAE, 0x4F, 0x0C, 0x48, 0xDB, 0x61, 0xA1, 0xD1,
      0xA0, 0x3A, 0x6F, 0x05, 0x55, 0x8B, 0xAF, 0x3B,
      0x5F, 0xE5, 0x26, 0xCA, 0x0C, 0x07, 0x01, 0x96,
      0xF4, 0xD2, 0xA0, 0x4B, 0x15, 0x94, 0x25, 0x6D,
      0xDF, 0xB1, 0x63, 0xCB, 0xB7, 0xAE, 0x2D, 0xB6,
      0xF6, 0x1F, 0x26, 0x7F, 0x50, 0xDD, 0xAC, 0x43,
      0x9A, 0xED, 0xDB, 0x0C, 0x11, 0x3F, 0xC6, 0x97,
      0xEA, 0x6B, 0x0D, 0xD2, 0x1E, 0x8D, 0xB4, 0x37,
      0xF6, 0x7B, 0x0A, 0x7E, 0x67, 0x9F, 0x53, 0x11,
      0x4E, 0xBD, 0xB8, 0x25, 0xE8, 0xFE, 0xF8, 0x3A,
      0xF3, 0xF5, 0x1A, 0x65, 0xA3, 0xAB, 0xCB, 0x3F,
      0x7D, 0x57, 0x95, 0xA8, 0x37, 0x41, 0x2C, 0x18,
      0x7C, 0x60, 0x75, 0x0A, 0x40, 0xA8, 0x56, 0x46,
      0x56, 0x54, 0xDC, 0xFA, 0x93, 0xE0, 0xCC, 0xB4,
      0x06, 0x6B, 0x32, 0x4D, 0x55, 0x20, 0xEF, 0x2E,
      0xAD, 0x4E, 0xD8, 0x3C, 0xBD, 0x0B, 0x36, 0x1A,
      0x7D, 0x17, 0x7A, 0xC4, 0x59, 0xCF, 0x37, 0xA1,
      0x74, 0xA7, 0xCD, 0x93, 0x57, 0x84, 0xD6, 0x82,
      0xCE, 0xDB, 0xF7, 0x2B, 0x9C, 0x2D, 0x0A, 0xF0,
      0x2C, 0x3A, 0x72, 0xA2, 0xDE, 0x79, 0xEF, 0x53,
      0x61, 0xC7, 0x17, 0xE9, 0x5D, 0xDF, 0x9D, 0xC3,
      0x8F, 0x95, 0x30, 0xBC, 0xCB, 0xAC, 0x7B, 0x8D,
      0x17, 0x25, 0xF3, 0x39, 0x30, 0xC0, 0xA0, 0x37,
      0x08, 0x06, 0x5D, 0x3F, 0xC5, 0x7F, 0x85, 0x61,
      0xD4, 0xB2, 0xEB, 0x1C, 0xA8, 0x48, 0x62, 0xCC,
      0xDD, 0x7B, 0xBA, 0x57, 0x78, 0xA2, 0xDE, 0x3C,
      0x74, 0x2F, 0xEE, 0x4D, 0x49, 0x5B, 0x06, 0x79,
      0x07, 0x3A, 0x87, 0xD2, 0xB9, 0x09, 0x75, 0x84,
      0x50, 0x6D, 0x15, 0x8D, 0x62, 0x88, 0x48, 0xC3,
      0x31, 0x71, 0x44, 0x14, 0x61, 0x97, 0x22, 0x37,
      0x4D, 0x46, 0xB9, 0x20, 0xFF, 0x3A, 0x2B, 0x44,
      0x69, 0xA0, 0x6B, 0x22, 0xF6, 0x3A, 0x9F, 0xEF,
      0x20, 0xE8, 0xF1, 0x68, 0x8B, 0x0E, 0xB4, 0xDC,
      0x0D, 0x11, 0x4A, 0x0D, 0x87, 0xED, 0x8D, 0x64,
      0x7B, 0x12, 0xE8, 0x5C, 0x2A, 0x7D, 0x45, 0x2E,
      0x7B, 0x78, 0x4F, 0x87, 0x3C, 0x20, 0xF7, 0xFB,
      0xC2, 0x6F, 0x3E, 0xC0, 0x7B, 0x58, 0xFD, 0x93,
      0xDD, 0x98, 0xC3, 0x7E, 0xE9, 0xC5, 0x48, 0xC4,
      0x08, 0x15, 0xD1, 0xE0, 0x50, 0xCB, 0xCD, 0x99,
      0xED, 0xBE, 0xB2, 0x12, 0xD8, 0x0A, 0x44, 0xF9,
      0x8A, 0x90, 0xA7, 0x99, 0x85, 0x91, 0xBF, 0x9D,
      0x79, 0xC0, 0xD7, 0x7A, 0x48, 0x0C, 0x5C, 0x88,
      0x84, 0x6B, 0x28, 0x4E, 0xF8, 0x4F, 0x70, 0xC7,
      0xAB, 0x6E, 0x28, 0x71, 0x14, 0x7F, 0x79, 0xEE,
      0x45, 0x9D, 0xE0, 0xAC, 0xEE, 0xD2, 0x86, 0xF3,
      0xAA, 0x7E, 0xA8, 0x37, 0xF4, 0x95, 0x76, 0x31,
      0xAB, 0x7A, 0xE0, 0x1F, 0x90, 0x74, 0x93, 0x06,
      0x5A, 0x60, 0xC5, 0x25, 0xAB, 0x3D, 0xDE, 0x2B,
      0x52, 0xD0, 0xDC, 0x82, 0x20, 0x5F, 0x90, 0x13,
      0xA4, 0xCC, 0x82, 0xD9, 0x13, 0xDE, 0x38, 0x19,
      0xF2, 0x52, 0x8B, 0x73, 0xE0, 0xEC, 0xA2, 0x5E,
      0xAB, 0x0B, 0x54, 0x0E, 0x0D, 0xA8, 0x5A, 0x6F };
    init();
    message_type = spark_protocol.received_message(ciphertext, 528);
    CHECK_EQUAL(CoAPMessageType::KEY_CHANGE, message_type);
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageRecognizesUpdateBegin)
  {
    uint8_t ciphertext[16] = {
      0x32, 0x28, 0x65, 0x77, 0x5B, 0xEE, 0xA8, 0x08,
      0xA9, 0xC6, 0x2F, 0x76, 0x44, 0x1A, 0xFF, 0x91 };
    init();
    message_type = spark_protocol.received_message(ciphertext, 16);
    CHECK_EQUAL(CoAPMessageType::UPDATE_BEGIN, message_type);
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageRecognizesChunk)
  {
    uint8_t ciphertext[96] = {
      0x59, 0xE4, 0xEA, 0xC2, 0xE2, 0x4B, 0x0D, 0xEE,
      0xDC, 0x0F, 0x9C, 0x08, 0x02, 0x21, 0xA8, 0xB3,
      0xCC, 0xE4, 0xE2, 0xA8, 0x7E, 0xE4, 0x9A, 0xC3,
      0xD6, 0x14, 0x4A, 0x8B, 0x2F, 0xCF, 0x45, 0xEE,
      0xC8, 0x14, 0x13, 0x50, 0x17, 0xBA, 0xD6, 0x14,
      0xCA, 0xA0, 0xF5, 0x54, 0x40, 0xFC, 0x1F, 0xE2,
      0x9B, 0xD0, 0xD5, 0x6D, 0x59, 0xEE, 0xE5, 0xC6,
      0x21, 0x19, 0x5D, 0x0D, 0x12, 0xCF, 0x9D, 0x48,
      0xD6, 0x75, 0x7B, 0x23, 0x6E, 0x31, 0xB7, 0x85,
      0x7E, 0x3D, 0xAB, 0x54, 0x7D, 0x27, 0x32, 0x70,
      0xA2, 0x08, 0x1C, 0xB1, 0x99, 0xDE, 0xF1, 0x63,
      0x5A, 0x33, 0x92, 0xDB, 0xE3, 0xC5, 0xDF, 0x6D };
    init();
    message_type = spark_protocol.received_message(ciphertext, 96);
    CHECK_EQUAL(CoAPMessageType::CHUNK, message_type);
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageRecognizesUpdateDone)
  {
    uint8_t ciphertext[16] = {
      0x5C, 0xC2, 0x80, 0x64, 0xAC, 0x11, 0xF4, 0x33,
      0x32, 0x82, 0x05, 0x7A, 0x9E, 0x8F, 0xAD, 0x2A };
    init();
    message_type = spark_protocol.received_message(ciphertext, 16);
    CHECK_EQUAL(CoAPMessageType::UPDATE_DONE, message_type);
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageRecognizesDescribe)
  {
    uint8_t ciphertext[16] = {
      0xd5, 0xb7, 0xf7, 0xfe, 0x9f, 0x2d, 0xca, 0xac,
      0xda, 0x15, 0x10, 0xa3, 0x27, 0x8b, 0xa7, 0xa9 };
    init();
    message_type = spark_protocol.received_message(ciphertext, 16);
    CHECK_EQUAL(CoAPMessageType::DESCRIBE, message_type);
  }

  TEST_FIXTURE(CoAPFixture, ReceivedMessageRecognizesHello)
  {
    uint8_t ciphertext[16] = {
      0x89, 0x5f, 0xeb, 0x18, 0x07, 0xba, 0x1d, 0xbf,
      0x11, 0x26, 0x55, 0x04, 0x75, 0x28, 0x2a, 0xef };
    init();
    message_type = spark_protocol.received_message(ciphertext, 16);
    CHECK_EQUAL(CoAPMessageType::HELLO, message_type);
  }

  TEST_FIXTURE(CoAPFixture, HelloMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0xf2, 0x10, 0x31, 0x66, 0x42, 0xf4, 0x64, 0xea,
      0xf7, 0xb8, 0x6e, 0x41, 0xce, 0x3a, 0xc7, 0x38 };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.hello(buf);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, KeyChangedMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0xba, 0xcc, 0x7f, 0x8f, 0x36, 0x61, 0x5f, 0x8f,
      0x82, 0xb4, 0xd1, 0x9d, 0x99, 0xb1, 0xa4, 0xeb };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.key_changed(buf, 0x99);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, FunctionReturnIntMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0x9c, 0x70, 0x6b, 0xdd, 0xda, 0xab, 0x6c, 0x55,
      0x10, 0x15, 0x97, 0xe7, 0x2c, 0xce, 0x2f, 0xc8 };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.function_return(buf, 0xc3, 42);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, VariableValueBoolMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0x78, 0x42, 0x6f, 0x07, 0x85, 0x9c, 0x44, 0x5b,
      0x5d, 0x70, 0x09, 0x40, 0xc3, 0x0b, 0xd1, 0x86 };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.variable_value(buf, 0x5f, false);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, VariableValueIntMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0xf2, 0xfb, 0x96, 0x4c, 0x41, 0x88, 0x84, 0xe2,
      0x1c, 0xfc, 0x1b, 0xd7, 0x49, 0x5e, 0x2e, 0x58 };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.variable_value(buf, 0x5e, -98765);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, VariableValueDoubleMatchesOpenSSL)
  {
    uint8_t expected[32] = {
      0x82, 0x7d, 0xa6, 0xfd, 0x90, 0x83, 0xba, 0xcc,
      0x0e, 0x2f, 0x9f, 0xbc, 0xa8, 0xf0, 0x27, 0xe2,
      0xc7, 0x1b, 0xb1, 0x7b, 0xd5, 0x3c, 0x39, 0x4b,
      0x7d, 0xc8, 0x59, 0x91, 0xb2, 0xc8, 0xf2, 0xd4 };
    unsigned char buf[32];
    memset(buf, 0, 32);
    init();
    spark_protocol.variable_value(buf, 0x5d, -104.858);
    CHECK_ARRAY_EQUAL(expected, buf, 32);
  }

  TEST_FIXTURE(CoAPFixture, VariableValueStringMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0x10, 0x2e, 0xf2, 0x37, 0xb2, 0x14, 0xb4, 0xec,
      0x46, 0x9d, 0xc9, 0x70, 0xc1, 0x56, 0x59, 0x12 };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.variable_value(buf, 0x5c, "woot", 4, 16);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, VariableValueStringErrorIfBufTooShort)
  {
    uint8_t expected[16] = {
      0x2a, 0x34, 0xf2, 0x85, 0x30, 0x90, 0x16, 0x23,
      0xb5, 0x80, 0xa1, 0x9d, 0x95, 0x0a, 0xc7, 0x0b };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    int error = spark_protocol.variable_value(buf, 0x5b, "Long string", 11, 16);
    CHECK_EQUAL(1, error);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, EventMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0xfa, 0xe4, 0x18, 0x59, 0x71, 0x3c, 0xed, 0xf6,
      0x37, 0xc3, 0x1d, 0xbb, 0x4f, 0x29, 0x25, 0xcd };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.event(buf, "temp", 4);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, EventWithDataMatchesOpenSSL)
  {
    uint8_t expected[32] = {
      0xd6, 0x05, 0xd1, 0xcf, 0xe2, 0xa7, 0x2b, 0xe9,
      0x9d, 0x68, 0x74, 0x9d, 0x24, 0xc5, 0x02, 0xed,
      0x02, 0x6d, 0x61, 0x18, 0xdb, 0x02, 0xb7, 0x86,
      0x6c, 0x86, 0x4c, 0x70, 0x22, 0x31, 0x93, 0x4e };
    unsigned char buf[32];
    memset(buf, 0, 32);
    init();
    spark_protocol.event(buf, "temp", 4, "22.3", 4);
    CHECK_ARRAY_EQUAL(expected, buf, 32);
  }

  TEST_FIXTURE(CoAPFixture, ChunkReceivedMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0xa7, 0x6e, 0x20, 0xe7, 0x4a, 0x5c, 0x82, 0xe9,
      0xec, 0x27, 0xe9, 0xe0, 0x75, 0x09, 0xb8, 0x6a };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.chunk_received(buf, 0x01, ChunkReceivedCode::OK);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, UpdateReadyMatchesOpenSSL)
  {
    uint8_t expected[16] = {
      0x29, 0xcd, 0x4e, 0x0c, 0x08, 0xe2, 0xc8, 0xbd,
      0x95, 0xfe, 0xca, 0x49, 0x1a, 0x4b, 0x20, 0x33 };
    unsigned char buf[16];
    memset(buf, 0, 16);
    init();
    spark_protocol.update_ready(buf, 0x10);
    CHECK_ARRAY_EQUAL(expected, buf, 16);
  }

  TEST_FIXTURE(CoAPFixture, DescriptionMatchesOpenSSL)
  {
    uint8_t expected[32] = {
      0xac, 0xc9, 0x8f, 0x76, 0x26, 0x76, 0xc9, 0x53,
      0xf5, 0xc2, 0x2a, 0x20, 0x70, 0xe6, 0x60, 0x28,
      0x54, 0x56, 0x8e, 0x87, 0xd4, 0x1b, 0x16, 0x7b,
      0xfe, 0xdc, 0x21, 0x6c, 0x1c, 0x59, 0xc5, 0x94 };
    unsigned char buf[32];
    memset(buf, 0, 32);
    init();
    const char *fnames[1];
    fnames[0] = "brew";
    spark_protocol.description(buf, 0x66, fnames, 1);
    CHECK_ARRAY_EQUAL(expected, buf, 32);
  }
}
