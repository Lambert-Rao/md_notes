1. web向服务器请求第三方登录登录, 服务器返回github第三方登录`uri`
> `uri`包含`response_type`(认证方式,比如code), `client_id`, `redirect_uri`, `scope`表示授权范围
2. 用户点击`uri`, 进入github, github询问用户是否同意授权指定范围的登录请求
3. 用户同意, 返回到`redirect_uri`, 同时会附带一个授权码code
```text
https://a.com/callback?code=AUTHORIZATION_CODE
```
4. 这时, 后端通过刚才的`uri`拿到了`code`, 就可以向github发送一个令牌请求:
```text
https://b.com/oauth/token?
 client_id=CLIENT_ID&
 client_secret=CLIENT_SECRET&
 grant_type=authorization_code&
 code=AUTHORIZATION_CODE&
 redirect_uri=CALLBACK_URL
```
> 上面 URL 中，client_id参数和client_secret参数用来让 B 确认 A 的身份（client_secret参数是保密的，因此只能在后端发请求）
> `redirect_uri`是令牌颁发后的回调地址.

5. github接到后端请求, 颁发一个`token`给后端(向redirect_uri发送数据)
6. 后端通过`token`向github资源服务器请求数据.

![oauth](https://miro.medium.com/v2/resize:fit:4800/format:webp/1*ULF38OTiNJNQZ4lHQZqRwQ.png)
![flowchart](https://cloudsundial.com/sites/default/files/2021-03/Web%20Server%202600.png)
