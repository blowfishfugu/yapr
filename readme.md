\## References pdf



1.0: [pdfreference1.0.pdf](https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/pdfreference1.0.pdf)



1.7: [pdfreference1.7.PDF32000\_2008.pdf](https://opensource.adobe.com/dc-acrobat-sdk-docs/pdfstandards/PDF32000_2008.pdf)



pdfarchive: [pdf-specification-archive](https://pdfa.org/resource/pdf-specification-archive/)



\## References zlib/flatedecode



rfc1950, rfc1951, rfc1952, rfc8118, rfc6713



billbird-datacompression-lectures: https://www.youtube.com/watch?v=J\_M2fvkOPkc\&list=PLU4IQLU9e\_OrY8oASHx0u3IXAL9TOdidm





\## iteration 1



read head(s) (magic-bytes), trailers, catalog, body



dependency on zlib: use uncompress on found streams, map objectids to byteoffset



focus on text, mark unparsable contents for later (DCT-jpegs..)

