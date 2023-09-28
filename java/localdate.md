> https://docs.oracle.com/javase/8/docs/api/java/time/LocalDateTime.html

### 转化
```java
ZonedDateTime atZone(ZoneId zone)
DayOfWeek getDayOfWeek()
//还有年月日时分秒以及更小的单位, 这些是取当前显示的
int getHour()
LocalDate toLocalDate()
LocalTime toLocalTime()

```

### 比较

```java
boolean equals(Object obj)
boolean isEqual(ChronoLocalDateTime<?> other)
boolean isAfter(ChronoLocalDateTime<?> other)
```

### 输出
```java
String format(DateTimeFormatter)
String toString()

```

### 运算
```java
//链式运算
LocalDateTime minus(long amountToSubtract, TemporalUnit unit)
//这个需要右边是一个long
LocalDateTime minusHours(long hours)
LocalDateTime withDayOfYear(int dayOfYear)

```

### 获取

```java
static LocalDateTime now()
static LocalDateTime of(int year, int month, int dayOfMonth, int hour, int minute, int second)
//这个`of`支持一系列参数, 只要参数在合适的位置表示正确的单位

static LocalDateTime of(LocalDate date, LocalTime time)

static LocalDateTime	ofEpochSecond(long epochSecond, int nanoOfSecond, ZoneOffset offset)
static LocalDateTime ofInstant(Instant instant, ZoneId zone)
static LocalDateTime parse(CharSequence text, DateTimeFormatter formatter)

```
