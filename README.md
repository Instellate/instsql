# instsql
A simple libpq wrapper that is trying to implement async compatibility.  
Why async compatibility? Cause libpqxx doesn't have async compatibility.

I would advise against using this library if you do not need asynchronous queries.  
I would instead recommend using [libpqxx](https://github.com/jtv/libpqxx) instead. 