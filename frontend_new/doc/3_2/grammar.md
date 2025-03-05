# 文法规则

---

## 前言

​	此文法仅针对样例c++源文件编写。规定大写字母为首的单词为非终结符，小写字母为首的单词为终结符，`...`表示可出现一次或多次，`?`表示可出现零次或多次，`etc.`表示省略。

---



## 主结构 (Program)

```latex
Program → Var_decl | Function_decl | Struct_decl | Expression_statement | Return_statement | etc.
```

`Program`是文法的起始符，定义了样例 C++ 子集的结构，通常由变量声明、函数声明、结构体声明、表达式语句或返回语句组成。

---



## 变量声明 (Var_decl)

```latex
Var_decl → Struct_decl | Type_keyword id ; | Type_keyword id = Expression ;
Struct_decl → struct id { Var_decl ... } id ;
```

`Var_decl` 可以被递归拆解为：

- `Struct_decl` 结构体声明
- `Type_keyword id ;` 声明变量，变量类型通过类型关键字（如 `int`、`float`）定义，后跟标识符（`identifier`）和分号（`;`）。
- 声明变量，变量类型通过类型关键字（如 `int`、`float`）定义，后跟标识符（`identifier`）和分号（`;`）。

`Struct_decl` 允许在程序中定义结构体类型，结构体由一个标识符和包含多个变量声明的字段组成。

---



## 函数声明 (Function_decl)

```latex
Function_decl → Type_keyword id ( Param ) { Statement }
              | Type_keyword id ( Param ) ;
Param → Type_keyword id (, Type_keyword id)? | ε
```

> [!WARNING]
>
> `Function_decl` 定义了函数声明的两种形式句号。
>
> 1. 第一种包含了函数体要注意的是! **在编写 `ParseFunction_decl` 的过程中要“消化”左右两大括号并更新词素指针。** 
> 2. 第二种仅有函数的声明, 和其他默认`Parse`函数一样, 出现`;`在函数内消化它并更新词素指针。

> [!TIP]
>
> `Param` 是形参列表, 可以是一个或多个函数, 使用逗号`,`分隔开。$ \epsilon $ 表示形参列表可以为空。

---



## 语句部分 (Statement)

```latex
Statement → Expression_statement | Return_statement | Block_statement | Declaration_statement | If_statement | While_statement
					｜
Expression_statement → Expression ;
Return_statement → return Expression ;
Block_statement → { Statement ... }
Declaration_statement → Var_decl | Functional_decl | etc.
If_statement → if ( Expression | ε ) Statement [else Statement]	% 此处的[]表示可能出现零次或多次
While_statement → while ( Expression ) Statement

```

`Statement` 定义了程序中的各种语句。

- `Expression_statement` 表达式语句，例如 a = 3 + 4;	a > b;
- `Return_statement` 返回语句，函数返回的值。
- `Block_statement` 块语句，用花括号包含一个或多个语句。
- `Declaration_statement` 声明语句，被消化为变量声明或函数声明及其他。
- `If_statement` 条件语句，后可跟随`else`分支。
- `While_statement` 循环语句。

---



## 表达式部分 (Expression, Term, Factor)

```latex
Expression → Term $ + | -  Term $ ?
Term → Factor $ * | /  Factor $ ?
Factor → id | Literal | ( Expression )
```

完整的表达式部分比较复杂，我们只讨论当前C++子集的四则运算部分。

常见的数学运算中，根据四则运算，操作符具有不同的优先级：

1. 括号 `()`优先级最高，首先处理括号中的表达式。
2.  乘除法 $*\ ÷$ 的优先级高于加减法 $+\ -$。
3. 加减法优先级最低。

然而，计算机只能顺序读取每个词素，无法像人眼那样直接找到优先级最高的操作符，因此需要采用递归下降解析方法来处理表达式的优先级。
先回头看一下用于表示四则运算表达式的文法。

1. `Expression` 表示加法和减法操作。它由 `Term` 开始，后面可能有一个或多个加法或减法操作。
2. `Term` 表示乘法和除法操作。它由 `Factor` 开始，后面可能有一个或多个乘法或除法操作。
3. `Factor` 表示因子，它可以是一个标识符（id）、字面量（Literal）或一个括号内的表达式。

在这个文法中，运算符优先级的处理是通过文法的结构来体现的：

- **括号**：由于括号包裹的内容通过 Factor 进行递归处理，因此括号中的表达式具有最高优先级。
- **乘除法**：由于括号包裹的内容通过 Factor 进行递归处理，因此括号中的表达式具有最高优先级。
- **加减法**：加法和减法通过 Expression 进行处理，它们位于最浅层。

---



## 字面量部分 (Literal)

```tex
Literal → Numeric_literal | String_literal | Char_literal | Boolean_literal
Numeric_literal → INTEGER | FLOATING
String_literal → STRING_LITERAL
Char_literal → CHARACTER
Boolean_literal → TRUE | FALSE
```

> [!CAUTION]
>
> 此部分全有大写组成的词素类型对应Token类型，是独立于文法规则的终结符。

---



## 类型关键字与关键字区分 (Type_keyword 和 keyword)

```tex
Type_keyword → int | float | double | char | void | bool
Keyword → if | else | for | return | struct | switch | case | etc.
```

Type_keyword 仅包括基本的数据类型，如 int、float、char 等，它们用于声明变量类型或函数的返回类型。

Keyword 包括程序控制结构的关键字，如 if、else、for、return 等。

---



## 运算符部分 (Operator)

```text
Operator → + | - | * | / | % | < | > | == | != | && | || | etc.
```

Operator 定义了常见的运算符，包括算术运算符（如 +、-、*）、比较运算符（如 ==、!=）以及逻辑运算符（如 &&、||）。
