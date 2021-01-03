# file_based_data_store

![compilation_testing1](https://github.com/shushill/file_based_data_store/blob/main/Screenshot%20from%202021-01-01%2020-23-15.png)
![compilation_testing2](https://github.com/shushill/file_based_data_store/blob/main/Screenshot%20from%202021-01-01%2021-13-36.png)

## file based data store

The data store will support the following functional requirements.

   1. It can be initialized using an optional file path. If one is not provided, it will reliably create itself in a reasonable location on the laptop.

   2. A new key-value pair can be added to the data store using the Create operation. The key is always a string - capped at 32chars. The value is always a JSON object - capped at 16KB.

   3.  If Create is invoked for an existing key, an appropriate error must be returned. 4. A Read operation on a key can be performed by providing the key, and receiving the value in response, as a JSON object.

   4. A Delete operation can be performed by providing the key.

   5. Every key supports setting a Time-To-Live property when it is created. This property is optional. If provided, it will be evaluated as an integer defining the number of seconds the key must be retained in the data store. Once the Time-To-Live for a key has expired, the key will no longer be available for Read or Delete operations.

   6. Appropriate error responses must always be returned to a client if it uses the data store in unexpected ways or breaches any limits.
   
   Following steps has been taken:
   
   1. Language: C++ 11 
   2. Library used: Multithreading in c++ and  nlohmann's json library to work with json objects in c++
   3. External database store: File based (a persistent store)
   4. Operating System used: Kali Linux OS
   5. Compiled using: g++ -std=c++11 key_value_file.cpp -pthread && ./a.out (screenshot given above)
   6. Time to Live (TTL) is varying and can be taken accordingly like 1000 seconds or 10000 seconds. etc..and so on
