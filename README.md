# gyoza-programming-language

---
I thought it'd be fun to try and write a simple programming language from scratch, so that's what \~Gyoza\~ is! I'm currently trying to figure out the rules for my language. Here's a list of criteria I'd like Gyoza to stick to:

1. Statically-typed. While it's nice to be able to write a function without declaring the types (which makes for faster development), I find that it makes it much harder to read. In addition, allowing a variable be *any* type can lead to some pretty bad bugs.
2. Not too verbose. I think it's gonna be hard to achieve this with (1) above, but I would like to reduce verbosity as much as possible.
3. Readable. I want this language to be easily readable, so one would be able to read code written by someone else with relative ease.

I'm not exactly sure how it's gonna look in the end, but below are some ideas that I currently have.

---
For defining variables and functions, I really like the idea of having the types defined on preceding lines, denoted with a #. I think it makes it obvious what types variables are, as well as specifying input/output types for functions. When reading the code, seeing a # will mean "hey, I've got something defined here, and here's what you need to know about it!" 

This was partially inspired by JavaDocs, which I've worked with in classes before. They're nice to read , since it clarifies the types of classes/functions, but it's not an enforced rule in Java like it will be here.

This checks off criterion 1, which is making the language strongly typed. I hope it doesn't make it too lengthy, so I'm still playing around with how it should look.

---
datatypes (keeping it basic for now)
```
int, float, string, bool, array (will not be supported just yet)
```

defining a variable
```
#<variable-type>
<variable-name> = <value>
```


examples:
```
#int
count = 0
```
```
#string
name = "Tim"
```

---
reassigning variables
```
<variable-name> = <new-value>
```

examples:
```
count = 1
count = count + 1
```

---
defining a function
```
#<input-variable1-type> <variable1-name>
#<input-variable2-type> <variable2-name>
#...
#<output-variable-type>
<function-name> = {
    ...
	return <some-variable>  
}
	
```

examples:
```
#int a
#int b
#int
sum = {
    return a + b
}
```
```
#string a
#string b
#string
concatenate = {
    return a + b
}
```
---
if/else statements (this doesn't look too good so maybe something different)
if/else:
```
<boolean-expression> ? {
    <some stuff here>
} / <2nd-boolean-expression> ? {
    <some stuff here>
} / <3rd-boolean-expression> ? {
    <some stuff here>
} / default ? {
    // this is the else
}

// this is a maybe, not sure if a one-line if statement is needed
<boolean-expression> ? <one liner>
```
if (no else):
```
<boolean-expression> ? {
    <some stuff here>
}
```

examples:
```
#int
number = 5

number > 5 ? {
    print(5)
} / default ? {
    print("not greater than 5")
}
```
---
loops (will not be supported yet)

for a range of numbers
```
#int
i = 0
for (i to 10 by 1)
    // i goes from 0 to 9 in increments of 1
```
foreach over a collection (just array for now)
```
#int[]
collection = [1, 2, 3];

foreach (element in collection)
    // loops by element through collection
```
while loop
```
while (<boolean-statement>) {
    // will keep looping until boolean statement is false
}
    
```
