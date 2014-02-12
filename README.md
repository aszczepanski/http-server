# sk-http

This project is an implementation of simple HTTP-based file server. Functionalities include uploading, downloading and deleting files over HTTP.

## Building

```
QTDIR=/Users/myself/Qt/5.2.0/clang_64/ cmake .
make
```

## Running

```
bin/server
bin/client
```

## Server

The server uses HTTP protocol to serve files from the filesystem as well as save and delete them. By default server runs on port 8080. Files are saved in './root_directory' relative to project root.

### Downloading a file

```
> GET http://localhost:8080/fileurl

< 200 Ok
< data
```

### Uploading a file

```
> PUT http://localhost:8080/fileurl
>
> data

< 201 Created
```

### Deleting a file

```
> DELETE http://localhost:8080/fileurl

< 204 No Content
```

## HTTP Client

The Client is an application written in C++ and Qt5 framework. Most of the implementation is in the uploaderwindow.cpp file. Users can upload and download files using respective tabs, as well as see the log of the operation.
