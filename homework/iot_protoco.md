**HTTP协议**

HTTP（HyperText Transfer Protocol，超文本传输协议）是用于传输超媒体文档（如HTML）的应用层协议。它被设计用来通过网络传输数据，包括文本、图像、音频、视频等。由于其简单且强大的特性，HTTP协议广泛应用于各种场景，包括工业互联网。

在工业互联网（Industrial Internet of Things, IIoT）中，HTTP协议常常用来在设备和云服务器之间进行数据传输。比如，设备可以使用HTTP协议向服务器发送设备状态、传感器数据，或接收来自服务器的指令。服务器可以使用HTTP协议接收设备的数据，或向设备发送指令。

HTTP支持多种方法，包括GET、POST、PUT、DELETE等，它们分别对应于不同的操作，例如获取数据、发送数据、更新数据和删除数据。

HTTP请求和响应都由三部分组成：起始行、头部和主体。起始行包含了方法、URL和HTTP版本；头部包含了一些元数据，如内容类型、内容长度等；主体则包含了实际的数据。

**MIME类型**

MIME（Multipurpose Internet Mail Extensions，多用途互联网邮件扩展）是一种用来描述和标记数据内容类型的互联网标准。在HTTP协议中，MIME类型常常用在“Content-Type”和“Accept”头部，用来表示发送或接收的数据的类型。

MIME类型是由两部分组成的：大类和小类，用“/”分隔。例如，文本文件的MIME类型是"text/plain"，JPEG图像的MIME类型是"image/jpeg"，JSON数据的MIME类型是"application/json"。

在工业互联网中，MIME类型可以帮助设备和服务器正确地处理数据。例如，如果设备向服务器发送一个JPEG图像，那么它可以在HTTP请求的“Content-Type”头部中使用"image/jpeg"，这样，服务器就知道它需要以图像的方式来处理接收到的数据。

同时，设备也可以在HTTP请求的“Accept”头部中使用特定的MIME类型，告诉服务器它希望接收哪种类型的数据。例如，如果设备只能处理JSON数据，那么它可以发送一个带有"Accept: application/json"头部的HTTP请求，这样，服务器就知道它需要返回JSON数据。

**Base64编码在工业互联网中的应用**

在工业互联网（Industrial Internet of Things，IIoT）的环境中，传感器和设备经常需要将各种类型的数据发送到云服务器。这些数据可能包括文本、数字、二进制数据，以及图片、音频、视频等。然而，网络传输协议通常设计为最好处理文本数据，因此对于非文本的二进制数据，如图片、音频和视频等，直接传输可能会出现问题。

这时候，Base64编码就能派上用场。Base64是一种基于64个可打印字符来表示二进制数据的表示方法。通过Base64编码，可以将二进制数据转换为由A-Z、a-z、0-9、+和/这64个字符组成的字符串，这样，就可以在只支持文本数据的网络协议中传输二进制数据。

例如，一个工业相机可能需要将拍摄的图片发送到云服务器。由于图片是二进制数据，所以相机可以首先将图片数据进行Base64编码，然后再通过HTTP或MQTT等协议发送到服务器。

**Base64编码的基本原理**

Base64编码的基本原理很简单。首先，将每三个字节的二进制数据分成四组，每组六位。然后，将这四组数据分别转换为0-63的十进制数。最后，将这四个十进制数映射到Base64的64个字符中，得到四个字符的编码结果。

如果原始数据的字节数不是3的倍数，那么在编码时可以使用填充字符（通常是"="）来补齐。例如，如果原始数据只有两个字节，那么编码结果将有三个字符和一个填充字符；如果原始数据只有一个字节，那么编码结果将有两个字符和两个填充字符。



### **图片传输请求示例**

工业设备（相机）拍摄照片，经过自动预处理之后，通过http请求将数据发送到云端服务器，服务器时刻监听服务，当收到数据后，使用模型处理接收到的图片，并把数据更新到数据库中。同时，服务器可以接收监控请求信息，监控请求返回统计数据。

#### 上传图片示例

```http
POST /api/uploadImage HTTP/1.1
Host: center-server.com/image
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW

------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="timestamp"

2023-06-04T08:00:00Z
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="deviceName"

Factory-Zone1-Device-Sensor
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="deviceUUID"

1f346544-027f-11ee-be56-0242ac120002
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="imageType"

jpg
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="imageFile"; filename="image.jpg"
Content-Type: image/jpeg

/9j/4AAQSkZJRgABAQEAYABgAAD/2wBDAAgGBgcGBQgHBwcJCQgKDBQNDAsLDBkSEw8UHRof
Hh0aHBwgJC4nICIsIxwcKDcpLDAxNDQ0Hyc5PTgyPC4zNDL/2wBDAQkJCQwLDBgNDRgyIRwh
MjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjIyMjL/wAAR
CAABAAEDASIAAhEBAxEB/8QAHwAAAQUBAQEBAQEAAAAAAAAAAAECAwQFBgcICQoL/8QAtRAA
AgEDAwIEAwUFBAQAAAF9AQIDAAQRBRIhMUEGE1FhByJxFDKBkaEII0KxwRVS0fAkM2JyggkK
FhcYGRolJicoKSo0NTY3ODk6Q0RFRkdISUpTVFVWV1hZWmNkZWZnaGlqc3R1dnd4eXqDhIWG
h4iJipKTlJWWl5iZmqKjpKWmp6ipqrKztLW2t7i5usLDxMXGx8jJytLT1NXW19jZ2uHi4+Tl
5ufo6erx8vP09fb3+Pn6/8QAHwEAAwEBAQEBAQEBAQAAAAAAAAECAwQFBgcICQoL/8QAtREA
AgECBAQDBAcFBAQAAQJ3AAECAxEEBSExBhJBUQdhcRMiMoEIFEKRobHBCSMzUvAVYnLRChYk
NOEl8RcYGRomJygpKjU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hpanN0dXZ3eHl6goOE
hYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3uLm6wsPExcbHyMnK0tPU1dbX2Nna4uPk
5ebn6Onq8vP09fb3+Pn6/9oADAMBAAIRAxEAPwD3+iiigD//2Q==
------WebKitFormBoundary7MA4YWxkTrZu0gW--

```

- `POST /api/uploadImage HTTP/1.1` 开始一个新的POST请求，向服务器发送图片。
- `Host: cloud-server.com` 指定了服务器的域名。
- `Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW` 指定了内容类型为multipart/form-data，并设置了分隔符。
- 每个`------WebKitFormBoundary7MA4YWxkTrZu0gW`都是一个边界，表示一个新的数据部分的开始。
- `Content-Disposition: form-data; name="timestamp"` 等行定义了表单数据的名字，例如时间戳、设备名、设备编号、图片类型等。
- `{Base64-encoded image data}`是Base64编码的图片数据。
- 请求结束的标志是 `------WebKitFormBoundary7MA4YWxkTrZu0gW--`，注意这个边界和其他的边界有所不同，它的后面多了两个破折号（--）。

服务器处理日志

```
[Information] -14653- 2023-06-06  Request method: POST, Request URI: /api/uploadImage, Content-Type: multipart/form-data;
[Information] -14653- 2023-06-06  Device info received: Factory-Zone1-Device-Sensor, UUID: 1f346544-027f-11ee-be56-0242ac120002
[Information] -14653- 2023-06-06  Image Type: jpg, File received: image.jpg
[Information] -14653- 2023-06-06  Model processing started
[Information] -14653- 2023-06-06  Model processing completed successfully
[Information] -14653- 2023-06-06  Result image generated: result.jpg
[Information] -14653- 2023-06-06  Database update started
[Information] -14663- 2023-06-06  Database updated with new image and processing results successfully
[Information] -14663- 2023-06-06  Response method: POST, Response URI: /api/uploadImage, Content-Type: multipart/form-data;
[Information] -14663- 2023-06-06  Response message: Image processed successfully
[Information] -14663- 2023-06-06  End of request processing
```

**服务器处理结果response**

```http
HTTP/1.1 200 OK
Server: IndustrialCloudServer/1.0
Date: Mon, 04 Jun 2023 09:01:15 GMT
Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW

------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="timestamp"

2023-06-04T09:01:15Z
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="deviceName"

Factory-Zone1-Device-Sensor
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="deviceUUID"

1f346544-027f-11ee-be56-0242ac120002
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="imageType"

jpg
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="resultImage"; filename="result.jpg"
Content-Type: image/jpeg

/9j/4AAQSkZJRgABAQEAYABgAAD/4QBARXhpZgAASUkqAAgAAAABAGmHBAABAAAAGgAAAAAA
AAACAAKgCQABAAAAAQAAAAOgCQABAAAAAQAAAAAAAAD/2wBDAAMCAgMCAgMDAwMEAwMEBQgF
BQQEBQoHBwYIDAoMDAsKCwsNDhIQDQ4RDgsLEBYQERMUFRUVDA8XGBYUGBIUFRT/2wBDAQME
BAUEBQkFBQkUDQsNFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQUFBQU
FBQUFBQUFBT/wAARCAABAAEDASIAAhEBAxEB/8QAHwAAAQUBAQEBAQEAAAAAAAAAAAECAwQF
BgcICQoL/8QAtRAAAgEDAwIEAwUFBAQAAAF9AQIDAAQRBRIhMUEGE1FhByJxFDKBkaEII0Kx
wRVS0fAkM2JyggkKFhcYGRolJicoKSo0NTY3ODk6Q0RFRkdISUpTVFVWV1hZWmNkZWZnaGlq
c3R1dnd4eXqDhIWGh4iJipKTlJWWl5iZmqKjpKWmp6ipqrKztLW2t7i5usLDxMXGx8jJytLT
1NXW19jZ2uHi4+Tl5ufo6erx8vP09fb3+Pn6/8QAHwEAAwEBAQEBAQEBAQAAAAAAAAECAwQF
BgcICQoL/8QAtREAAgECBAQDBAcFBAQAAQJ3AAECAxEEBSExBhJBUQdhcRMiMoEIFEKRobHB
CSMzUvAVYnLRChYkNOEl8RcYGRomJygpKjU2Nzg5OkNERUZHSElKU1RVVldYWVpjZGVmZ2hp
anN0dXZ3eHl6goOEhYaHiImKkpOUlZaXmJmaoqOkpaanqKmqsrO0tba3uLm6wsPExcbHyMnK
0tPU1dbX2Nna4uPk5ebn6Onq8vP09fb3+Pn6/9oADAMBAAIRAxEAPwD8qqKKKAP/2Q==
------WebKitFormBoundary7MA4YWxkTrZu0gW
Content-Disposition: form-data; name="result"

Image processed successfully
------WebKitFormBoundary7MA4YWxkTrZu0gW--

```

- `HTTP/1.1 200 OK`： 这是HTTP响应的起始行，表示HTTP版本为1.1，响应的状态码为200，状态码的文本解释为OK。
- `Server: IndustrialCloudServer/1.0`：此行表示服务器的名称和版本。
- `Date: Mon, 04 Jun 2023 09:01:15 GMT`：此行表示此响应消息的时间戳。
- `Content-Type: multipart/form-data; boundary=----WebKitFormBoundary7MA4YWxkTrZu0gW`：此行定义了HTTP响应的内容类型是`multipart/form-data`，并且设定了数据分隔符。
- 后续的`------WebKitFormBoundary7MA4YWxkTrZu0gW` 表示每个数据部分的起始。
- `Content-Disposition: form-data; name="timestamp"`等行定义了每个部分的名字，如时间戳、设备名称、设备编号、图片类型和处理后的图片。
- ``{Base64-encoded image data}` 是处理后的图片数据，该数据使用Base64编码。
- `Content-Disposition: form-data; name="result"`定义了处理结果的部分名。
- `Image processed successfully`表示处理结果的具体信息。
- `------WebKitFormBoundary7MA4YWxkTrZu0gW--`表示响应内容的结束，注意它与其他边界的不同之处在于它后面多了两个破折号（--）。



#### 管理者API

```http
GET /api/queryDeviceResults HTTP/1.1
Host: cloud-server.com
Authority: Bearer eyJhbGciOiJIUzI1NiJ9.eyJleHAiOjE2ODU4NTA3MTguMzY0MzksImlhdCI6MTY4NTg0NzExOC4zNjQzODYsImlzcyI6ImNoYXJTZXJ2ZXJMYW1iZXJ0IiwibmJmIjoxNjg1ODQ3MTE4LjM2NDM4OCwidXNlcl9pZCI6MCwidXNlcm5hbWUiOiJBIn0.rxLLNm2vbUXWEyE3_0aYpVujADCF0qjM_p_RFCOm8ZM
```

返回数据

```http
HTTP/1.1 200 OK
Server: IndustrialCloudServer/1.0
Date: Mon, 04 Jun 2023 09:01:15 GMT
Content-Type: application/json

{
  "code": 0,
  "data": [
    {
      "timestamp": "2023-06-04T08:00:00Z",
      "deviceName": "Factory-Zone1-Device-Sensor",
      "deviceUUID": "1f346544-027f-11ee-be56-0242ac120002",
      "hasDefect": false,
      "imageURL": "http://cloud-server.com/images/processed/1.jpg"
    },
    {
      "timestamp": "2023-06-04T08:05:00Z",
      "deviceName": "Factory-Zone2-Device-Sensor",
      "deviceUUID": "1f346544-027f-11ee-be56-0242ac120003",
      "hasDefect": true,
      "imageURL": "http://cloud-server.com/images/processed/2.jpg"
    }
    // 更多数据项...
  ]
}

```

- `HTTP/1.1 200 OK`：这是HTTP响应的起始行，它表示使用的HTTP版本为1.1，响应状态码为200，状态码的文本解释为OK。
- `Server: IndustrialCloudServer/1.0`：此行表示响应的服务器名称及其版本。
- `Date: Mon, 04 Jun 2023 09:01:15 GMT`：此行表示响应生成的时间。
- `Content-Type: application/json`：此行表明了响应数据的媒体类型是JSON格式。
- `{}` 内的内容是响应的主体，包含的是JSON格式的数据。
- `"code": 0,` 表示响应的状态码，0通常表示请求处理成功。
- `"data": [...]` 这部分包含了请求的实际数据，是一个数组。数组中每个元素都是一个对象，每个对象包含了时间戳（timestamp）、设备名（deviceName）、设备编号（deviceUUID）、是否有缺陷（hasDefect）以及图片链接地址（imageURL）等信息。





 
