 

Poco库的HTTPServerRequest和HTTPServerResponse类是用于处理HTTP请求和响应的。他们提供了许多用于获取和设置HTTP消息的方法。以下是一些常用的方法：

**HTTPServerRequest**:

- `getURI()`: 返回请求的URI（Uniform Resource Identifier）。
- `getMethod()`: 返回HTTP请求方法，如GET, POST, PUT, DELETE等。
- `getContentType()`: 返回请求的Content-Type头的值。这通常是表示请求体的MIME类型，如`application/json`，`text/html`等。
- `getContentLength()`: 返回请求体的长度。这是Content-Length头的值。
- `stream()`: 返回一个输入流，可以用来读取请求体的数据。

**HTTPServerResponse**:

- `setStatus(HTTPStatus status)`: 设置HTTP响应的状态码，如200，404，500等。
- `setContentType(const std::string& mediaType)`: 设置响应的Content-Type头的值。这通常表示响应体的MIME类型。
- `setContentLength(std::streamsize length)`: 设置响应体的长度。这设置Content-Length头的值。
- `send()`: 发送响应。返回一个输出流，可以用来写入响应体的数据。

关于处理JSON数据，由于HTTPServerRequest和HTTPServerResponse类并不直接提供处理JSON的方法，你需要使用其他库来序列化和反序列化JSON。例如，你可以使用Poco的JSON库。例如，下面是一个如何从HTTPServerRequest读取JSON请求体，以及如何向HTTPServerResponse写入JSON响应体的示例：

```
cppCopy codevoid handleRequest(Poco::Net::HTTPServerRequest &request, Poco::Net::HTTPServerResponse &response) {
    // 从请求中读取JSON
    Poco::JSON::Parser parser;
    auto json = parser.parse(request.stream()).extract<Poco::JSON::Object::Ptr>();

    // 处理JSON数据...
    std::string username = json->getValue<std::string>("username");

    // 创建一个JSON响应体
    Poco::JSON::Object::Ptr responseJson = new Poco::JSON::Object;
    responseJson->set("message", "Hello, " + username);

    // 设置响应头
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    response.setContentType("application/json");

    // 将JSON写入响应
    responseJson->stringify(response.send(), 3);
}
```

注意，以上代码中 `handleRequest` 函数应该是你自定义的处理请求的函数。在实际的项目中，你可能需要根据你的需求进行适当的修改。
