 

POCO ActiveRecord 用户指南
POCO ActiveRecord 框架

# !!!简介

POCO ActiveRecord 是一个基于 POCO 数据库库的简单轻量的对象-关系映射（ORM）框架。
POCO ActiveRecord 的主要目标是减轻开发者编写大量关于数据库查询的模板代码的工作负担，如通过 ID 查找对象、更新对象、删除对象或执行分页查询。正如其名字所示，该框架遵循了众所周知的[Active Record](https://en.wikipedia.org/wiki/Active_record_pattern )架构模式。它基于一个名为 <*ActiveRecord Compiler*>（或称为 <[arc]>）的代码生成器，并使用约定优于配置的方法。

# !!!入门

使用 ActiveRecord 框架的起点是一个 XML 文件。XML 文件描述了与数据库表对应的类及其关系。从这个 XML 文件中，ActiveRecord Compiler 生成对应的头文件和源文件，定义并实现相应的 C++ 类，以及为 POCO 数据库库提供类型处理器。

以下是这样一个 XML 文件的示例。该文件定义了两个类，一个 `Employee` 类（映射到名为 `employees` 的表），和一个 `Role` 类（映射到名为 `roles` 的表）。
```xml
  <project namespace="Sample">
    <class name="Employee" table="employees">
      <property name="id" type="uuid"/>
      <property name="name" type="string"/>
      <property name="ssn" type="string"/>
      <property name="role" type="int16" references="Role"/>
      <property name="manager" type="uuid" references="Employee" cardinality="?"/>
    </class>

    <class name="Role" table="roles" autoIncrementID="true">
      <property name="id" type="int16"/>
      <property name="name" type="string"/>
      <property name="description" type="string"/>
    </class>
  </project>
```

`Employee` 和 `Role` 之间存在 n:1 的关系（每个员工有且仅有一个角色）。此外，每个员工可以选择性地拥有一个经理，该经理也是一个 `Employee`。

属性名为 `id` 的属性被认为是主键，除非有另一个属性被指定为主键（在 `class` 元素中使用 `key` 属性）。也可以没有主键或 ID 列的对象（无键的活动记录）。

生成的 C++ 类将在 `Sample` 命名空间中，如 <[project]> 元素所指定。p

XML 文件中的定义对应于由以下 <[CREATE TABLE]> 语句构建的数据库模式：
```SQL
  CREATE TABLE employees (
    id CHAR(36) PRIMARY KEY,
    name VARCHAR(64),
    ssn VARCHAR(32),
    role INTEGER,
    manager CHAR(36)
  );

  CREATE TABLE roles (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(64),
    description VARCHAR(256));
```
如果数据库引擎支持，`employees` 表的 `id` 列也可以是 UUID。

使用上述XML文件（sample.xml）运行ActiveRecord

```bash
arc sample.xml
```

将在当前工作目录中创建以下文件：

```
  include/
    Sample/
      Employee.h
      Role.h
  src/
    Employee.cpp
    Role.cpp
```

生成的类派生自Poco::ActiveRecord::ActiveRecord类模板，并拥有所有在XML文件中定义的属性的访问方法，
以及在数据库中创建、更新和删除实例的方法。

ActiveRecord对象是引用计数的，每个生成的类都包含一个适合的Poco::AutoPtr<>的`Ptr`类型别名。

## !!上下文环境

ActiveRecord使用一个上下文（Poco::ActiveRecord::Context）类将对象绑定到数据库会话（Poco::Data::Session）。除了数据库会话外，
上下文也持有一个特定连接器的Poco::ActiveRecord::StatementPlaceholderProvider。这个类确保生成的SQL语句具有针对各自数据库后端的正确占位符。对大多数数据库后端来说，`?`占位符就足够了，但是PostgreSQL有一个不同的占位符格式（`$1`，`$2`等）。上下文的StatementPlaceholderProvider会处理这个问题。

每个ActiveRecord对象在进行任何数据库操作之前都必须与一个上下文关联。上下文对象相对轻量级，所以可以在需要的时候创建。上下文对象是引用计数的，所以只要至少还有一个ActiveRecord对象仍然引用它，上下文对象就会保持活动状态。

## !!创建一个对象

下面的代码片段展示了如何创建一个新的`Role`对象并将其插入到`roles`表中。

    Poco::Data::Session session("SQLite", "data.sqlite");
    Context::Ptr pContext = new Context(session);
    
    Role::Ptr pDeveloper = new Role;
    pDeveloper->name("Developer")
        .description("Developer role");
    
    pDeveloper->create(pContext);
----

如你所见，设置器（在这种情况下是`name()`，`description()`）可以进行链接。
`create()`方法将把对象绑定到一个上下文，然后执行一个`INSERT`语句将对象插入到`roles`表中。

## !!查找对象

下面的代码片段展示了如何通过ID（1）查找一个`Role`对象。

    Poco::Data::Session session("SQLite", "data.sqlite");
    Context::Ptr pContext = new Context(session);
    
    Role::Ptr pRole = Role::find(pContext, 1);
    std::cout
        << "name: " << pRole->name() << "\n"
        << "description: " << pRole->description() << std::endl;
----

## !!更新对象

更新对象涉及首先使用设置器函数更新相应的属性，然后调用`update()`方法。要更新一个
ActiveRecord对象，对象必须已经绑定到一个上下文。
从`find()`返回的对象，或者从查询返回的对象已经绑定到一个上下文。
注意，以下片段将省略会话和上下文设置代码。

    Role::Ptr pRole = Role::find(pContext, 1);
    pRole->description("New developer role");
    pRole->update();
----

## !!删除对象

绑定到一个上下文的对象可以通过调用`remove()`方法进行删除。

    Role::Ptr pRole = Role::find(pContext, 1);
    pRole->remove();
----

## !!查询

如果已知相应的ID，那么只通过它们的ID查找对象就够了。
然而，在大多数情况下，ActiveRecord对象将通过执行查询获得。为此，ActiveRecord框架提供了
Poco::ActiveRecord::Query类模板。Query模板必须用结果对象的类进行实例化。Query类将生成一个
`SELECT`语句。查询参数可以通过数据绑定指定。无论底层数据库后端如何，都可以使用`?`占位符。Query类将用后端的适当占位符替换它。
实际的查询参数是通过`bind()`方法绑定的。然后通过调用`execute()`方法执行查询。

Query的结果是一个包含返回对象指针（Poco::AutoPtr）的`std::vector`。

    Poco::ActiveRecord::Query<Role> query(pContext);
    const auto result = query
        .where("name = ?")
        .bind("Developer"s)
        .execute();
    for (const auto& pRole: result)
    {
        std::cout << pRole->description() << std::endl;
    }
----

`where()`方法的参数可以是任何SQL WHERE子句。请注意，你必须在WHERE子句中使用实际数据库表的列名，而不是属性名。

### !排序

可以通过调用`orderBy()`方法对Query的结果进行排序。
注意，`orderBy`的参数必须是表中的实际列名，而不是对象的属性名。列名后可以跟
`ASC`或`DESC`来指定方向。

    Poco::ActiveRecord::Query<Role> query(pContext);
    const auto result = query
        .where("name = ?")
        .bind("Developer"s)
        .orderBy("name ASC")
        .execute();
    for (const auto& pRole: result)
    {
        std::cout << pRole->description() << std::endl;
    }
----

### !分页

查询的结果可以通过指定一个偏移量和一个限制进行分页。
偏移量指定了要返回的第一个结果的索引，限制指定了返回的对象的最大数量。

要检索所有角色，分成每页10个角色，可以使用以下代码：

    std::size_t offset = 0;
    const std::size_t pageSize = 10;
    Poco::ActiveRecord::Query<Role> query(pContext);
    bool done = false;
    while (!done)
    {
        const auto result = query
            .orderBy("name")
            .offset(offset)
            .limit(pageSize)
            .execute();
    
        offset += result.size();
        done = result.empty();
    
        for (const auto& pRole: result)
        {
            // ...
        }
    
        query.reset();
    }
----

为了重新执行一个Query，首先必须调用`reset()`方法，如上面`while`循环的末尾所示。

### !筛选结果

除了使用`WHERE`子句筛选结果外，还可以用lambda表达式筛选结果。虽然`WHERE`是在数据库引擎中评估的，因此效率更高，但`filter()`方法允许一些额外的灵活性。

    Poco::ActiveRecord::Query<Role> query(pContext);
    query.filter(
        [](const Role& role)
        {
            return role.name() == "Senior Developer";
        }
    );
    
    const auto result = query.execute();
----

lambda表达式接收一个ActiveRecord对象的const引用，必须返回一个`bool`。如果返回`true`，则该对象包含在结果中，否则不包含。

### !关系

关系（在XML文件中以带有`references`属性的属性形式定义）可以通过两种访问器方法进行访问。第一种接受一个ActiveObject::Ptr作为参数或返回它，第二种接受一个键作为参数或返回它。接受键/ID值而非ActiveRecord的访问器，其方法名称会带有`ID`后缀。

在以下示例中，`role`属性是通过键值设置的，而`manager`属性是通过ActiveRecord对象设置的。

    Employee::Ptr pManager = new Employee;
    pManager->name("Bill Lumbergh").ssn("23452343").roleID(3);
    pManager->create(pContext);
    
    Employee::Ptr pEmployee = new Employee;
    pEmployee->name("Michael Bolton").ssn("123987123").roleID(2).manager(pManager);
    pEmployee->create(pContext);
----

### !自增键和插入时自动生成的UUID

ActiveRecord支持在插入ActiveRecord时自增键。要启用此功能，需要将`class`元素的`autoIncrementID`属性设置为`true`。插入这样的ActiveRecord对象时，执行`INSERT`语句后，键的实际值将从数据库中获取。当前，这是针对SQLite、MySQL/MariaDB和PostgreSQL实现的，使用适当的数据库特定机制。

当插入一个全null UUID的ActiveRecord时，将在执行`INSERT`语句之前生成一个随机UUID。

!无键的Active Record

可以定义没有ID或主键属性的类。对于这些对象，不会生成`find()`方法，也无法更新这些对象（`update()`将抛出Poco::NotImplementedException）。

可以通过执行Poco::ActiveRecord::Query来获取无键的ActiveRecord对象。

# !!!编译器XML参考

## !!支持的数据类型

以下数据类型可以在`type`属性中为属性指定，并映射到指定的C++类型。

    XML中的类型     C++类型
    ----------------------------
    bool            bool
    char            char
    int8            Poco::Int8
    uint8           Poco::UInt8
    int16           Poco::Int16
    uint16          Poco::UInt16
    int32           Poco::Int32
    uint32          Poco::UInt32
    int64           Poco::Int64
    uint64          Poco::UInt64
    float           float
    double          double
    dateTime        Poco::DateTime
    timestamp       Poco::Timestamp
    time            Poco::Data::Time
    date            Poco::Data::Date
    uuid            Poco::UUID
    string          std::string
----

注意：在创建底层数据库模式时，使用与XML中指定的数据类型兼容的数据库特定列类型是开发者的责任。

## !!元素和属性

### !project元素

`project`元素必须是XML文件中的根元素。
`project`元素接受以下属性：

   - `namespace`：为生成的类指定C++命名空间。可以指定多级命名空间，例如"MyProject::Data"。


 - `convertCamelCase`：如果设置为`true`，则将以驼峰形式指定的属性和类名（如`firstName`）转换为蛇形（`first_name`）以识别相应的列或表。默认为`false`。

### !class元素

`class`元素必须在`project`元素内部，接受以下属性：

  - `name`：指定类的名称。必须是有效的C++类名。必填。
  - `table`：指定相关数据库表的名称。如果未指定，则表名将从类名派生（见`project`元素中的`convertCamelCase`属性）。
  - `key`：指定主键列的名称。如果未指定，默认为`id`。
  - `autoIncrementID`：如果设置为`true`，则认为主键是自增的。插入新的ActiveObject时，主键为NULL，这将导致数据库分配新的键值。执行`INSERT`语句后，实际的键值将从数据库中获取。

### !property元素

`property`元素必须在`class`元素内部，接受以下属性：

  - `name`：指定变量的名称，这也用于getter和setter方法。必须是有效的C++变量或方法名。必填。
  - `column`：指定相关数据库列的名称。如果未指定，列名将从属性名派生（见`project`元素中的`convertCamelCase`属性）。
  - `type`：指定属性的数据类型。参见<*支持的数据类型*>以获得支持值的列表。必填。
  - `references`：指定关系目标类的名称。必须是在同一XML文档中定义的另一个类的名称。
  - `cardinality`：指定关系的基数。可以指定以下值：`?`表示零个或一个，`1`表示恰好一个（默认）。另外，`*`表示零个或更多，`+`表示一个或更多，但是当前没有为后两种基数生成访问器。
  - `nullable`：如果设置为`true`，将属性或列标记为可为空。在这种情况下，访问器方法将接受或返回Poco::Nullable<>值。
