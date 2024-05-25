# Ali namespace
Done by me, it has some cool features. Here are my faves:

`console.h`
It has the class console, that supports basically every standard type, and more!
There are also pretty ways of printing arrays/vectors, defined with `_JAVASCRIPT_STYLE_LOGGING`.

### Some examples:
#### Example 1:
`console.log(123);`

**Output**:
`123`

#### Example 2:
`console.log(L"Hello world!");`

**Output**:
`Hello world!`

_As you can see, there are no problems with wide characters._

#### Example 3:

`console.logp(213, ' ', 9.4f);`

**Output**:
`213 9.4`

_This one's like printf(), but doesn't require the beginning const char* parameter._

#### Example 4:
```
std::vector<int> x = {1,2,3,4,5};
console.log(x);
```

**Output**:

`(5) [1, 2, 3, 4, 5]`

_Works with arrays and vectors, and does a pretty job!_
