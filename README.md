# uap

Universal Application Platform

## APIs

All the APIs are in **uap** namespace, there are several C APIs and C++ APIs

The C++ APIs are are always interface based. They should be get by uapGetInterface


### C APIs


API | Description
----|----
uapInitialize | Initialize the UAP 
uapCreateApplication | Initialize the uap::IApplication interface
logPrint | print log

### C++ APIs(Interfaces)

The C++ APIs are all interfaces, they are exposed from UAP(uapbe) itself or the components


Interface | component|backend
----|----|----
uap::IAttributes| UAP |windows, linux(N/A)
uap::IImageEngine| imageengine| WIC, libpng(N/A)