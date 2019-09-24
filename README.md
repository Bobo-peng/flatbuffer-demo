# flatbuffer-demo
I have some questions:

- 1.if `memset(buffer+100, 0x00, sizeof(char)*50);`

  The result:

  ```
  size:204
  Verify success!
  city_name 0:Handan,area_code 0:0310
  Segmentation fault (core dumped)
  
  //stack info :
  Program received signal SIGSEGV, Segmentation fault.
  0x0000000000403b5e in flatbuffers::Vector<char>::size (this=0x0)
      at flatbuffers/flatbuffers.h:234
  234	  uoffset_t size() const { return EndianScalar(length_); }
  (gdb) info stack
  #0  0x0000000000403b5e in flatbuffers::Vector<char>::size (
      this=0x0) at flatbuffers/flatbuffers.h:234
  #1  0x0000000000401bb1 in flatbuffers::String::str (this=0x0)
      at flatbuffers/flatbuffers.h:490
  #2  0x0000000000401863 in main () at main.cpp:43
  ```

- 2. If `memset(buffer+100, 0x01, sizeof(char)*50);`

     the result:

     ```
     size:204
     Verify failed!
     ```

- 3.if `memset(buffer+100, 0x01, sizeof(char)*1);`

  the result:

  ```
  size:204
  Verify success!
  city_name 0:Handan,area_code 0:0310
  city_name 1:Shijiazhuang,area_code 1:0311
  city_name 2:Baodng,area_code 2:0312
  city_name 3:Zhangjiakou,area_code 3:0313
  ```

  

