package com.palv;

import java.io.*;
import java.security.NoSuchAlgorithmException;
import java.security.MessageDigest;

public class HashFromStringOrFile
{
    public static void main(String[] args) throws Exception {

        // TEST
        String stringToEncrypt = "alert('Hello, world.');";

        // qznLcsROx4GACP2dm0UCKCzCG+HiZ1guq6ZZDob/Tng=
        String encoded = generateHaah(stringToEncrypt,"sha-256");
        if(encoded.equals("qznLcsROx4GACP2dm0UCKCzCG+HiZ1guq6ZZDob/Tng=")){
            System.out.println("OK");
        }

        // real
        System.out.println(generateHashForFile("c:\\tmp\\text1.txt","SHA-512"));
    }

    /**
     *
     *
     * @param stringToEncrypt
     * @param algorithm
     *   MD2	The MD2 message digest algorithm as defined in RFC 1319.
     *   MD5	The MD5 message digest algorithm as defined in RFC 1321.
     *   SHA-1     Hash algorithms defined in the FIPS PUB 180-2.
     *   SHA-256   SHA-256 is a 256-bit hash function intended to provide 128 bits of security against collision attacks
     *   SHA-384   A 384-bit hash may be obtained by truncating the SHA-512 output.
     *   SHA-512   SHA-512 is a 512-bit hash function intended to provide 256 bits of security
     * @return
     * @throws NoSuchAlgorithmException
     * @throws IOException
     */
    private static String generateHaah(String stringToEncrypt, String algorithm) throws NoSuchAlgorithmException, IOException {
        MessageDigest digest = MessageDigest.getInstance(algorithm);
        byte[] hash = digest.digest(stringToEncrypt.getBytes());
        return java.util.Base64.getEncoder().encodeToString(hash);
    }

    /**
     *
     *
     * @param filename
     * @param algorithm
     *   MD2	The MD2 message digest algorithm as defined in RFC 1319.
     *   MD5	The MD5 message digest algorithm as defined in RFC 1321.
     *   SHA-1     Hash algorithms defined in the FIPS PUB 180-2.
     *   SHA-256   SHA-256 is a 256-bit hash function intended to provide 128 bits of security against collision attacks
     *   SHA-384   A 384-bit hash may be obtained by truncating the SHA-512 output.
     *   SHA-512   SHA-512 is a 512-bit hash function intended to provide 256 bits of security
     * @return
     * @throws NoSuchAlgorithmException
     * @throws IOException
     */
    private static String generateHashForFile(String filename, String algorithm) throws NoSuchAlgorithmException, IOException {
        MessageDigest messageDigest = MessageDigest.getInstance(algorithm);
        FileInputStream fis = new FileInputStream(filename);
        byte[] dataBytes = new byte[1024];
        int nread ;
        while ((nread = fis.read(dataBytes)) != -1) {
            messageDigest.update(dataBytes, 0, nread);
        };
        byte[] mdbytes = messageDigest.digest();
        return java.util.Base64.getEncoder().encodeToString(mdbytes);
    }
}
