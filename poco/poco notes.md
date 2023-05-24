 

### [RESTful API](https://apifox.com/blog/a-cup-of-tea-time-to-understand-restful-api/?gclid=CjwKCAjwpayjBhAnEiwA-7enazI6F-GZxj-6YwTAZL0eps_grCBghswHUDf3e3UfXzQh0jqduJoaBhoCRnAQAvD_BwE)

##### Uniform Interface（统一接口）

- 在一个完全遵循 RESTful 的团队里，后端只需要告诉前端 /users 这个 API，前端就应该知道:

​    获取所有用户：GET /users  

​    获取特定用户：GET /users/{id}  

​    创建用户：POST /users  

​    更新用户：PUT /users/{id}  

​    删除用户：DELETE /users/{id}

- 当 API 数量非常多，系统非常复杂时，RESTful 的好处会越来越明显。理解系统时，可以直接围绕一系列资源来理解和记忆。

##### Statelessness（无状态）

- 它指的是每个请求都是**独立的**，**没有前后关系**。服务器不保存客户端的状态信息，并且每个请求都必须包含所有所需的信息。
