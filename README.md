# HexaDeath

## An esoteric language focused around a lack of readability at a quick glance.

Built for the Windows `x86-64` platform, Linux support coming soon.
Written in `C++`.

Interprets `.hexd` files from the command line using "hxd (path to file)"

Type "hxd --help" if you need more information on the program!

## Language Explanation

### Basic Grammar
HexaDeath has a unique way of writing instructions. The programming language is, like binary, read **back-to-front**.
An example instruction would look like this:

`05 02 AB 01 01`

Let's tackle it from back to front, just like the interpreter.

The first digit, `01`, is the **Output Key**. This hex number specifies the number of outputs the call provides. Outputs can be used to fill variable values, like an input or an assign function.

The second digit, `01`, like the first, is the **Argument Key**. This hex number specifies the number of arguments the function will take.

Now, we get to the outputs. The number of output varies based on the function, as specified by the argument key, but our selected function has only one. So, the next hex digit, `AB`, is our output.

The next digit is the function call. For a list of all function calls, see below. The function we chose about is the `ASSIGN VAR` function, which takes one argument (the value) and gives one output (the variable the value will be passed to).

The rest of the digits (or as many as the argument key specifies) are the arguments of the function. For this, we have the value `05`.

Putting it all together, we have the pseudocode `LET VAR 171 = 5`

Simple, right?

### Function list
Below is a list of all functions currently supported in Hexadeath. This list will change and grow, but I do not plan on changing any old functions beyond expanding their capabilities while maintaining backwards-compatability.

`00` NULL

`01` NEW VAR 		              (1 arg: var id#)

`02` ASSIGN VAR 		          (1 arg: value; 1 out: var id#)

`03` INC VAR			            (1 arg: var id#)

`04` DEC VAR			            (1 arg: var id#)

`05` PRINT VALUE		          (1 arg: value)

`06` PRINT VAR		            (1 arg: var id#)

`07` INPUT TO VAR		          (1 out: var id#)

`08` VAR == VALUE		          (2 arg: var id#, value; 1 out: out var id#)

`09` VAR == VAR		            (2 arg: var 1 id#, var 2 id#; out: out var id#)

`0A` VAR > VALUE		          (2 arg: var id#, value; 1 out: out var id#)

`0B` VAR > VAR		            (2 arg: var 1 id#, var 2 id#; out: out var id#)

`0C` VAR < VALUE		          (2 arg: var id#, value; 1 out: out var id#)

`0D` VAR < VAR		            (2 arg: var 1 id#, var 2 id#; out: out var id#)

`0E` JUMP			                (1 arg: label id#)

`0F` JUMP IF NOT 0		        (2 args: var id#, label id#)

`10` JUMP IF 0		            (2 args: var id#, label id#)

`11` NEW LABEL		            (1 arg: label id#)

### Program Examples
The `Examples` folder (HexaDeath\Examples) contains a few example programs I have written to display HexaDeath's capability. The easiest way to run them is to run "hxd (path to source files)\HexaDeath\Examples\..."

The few examples I have right now are:

`hello.hexd`:          Hello, World!
`truth.hexd`:          Truth table program.
`nestedloops.hexd`:    A test for nesting loops in this program.
`countdown.hexd`:      Complex console output + arithmetic.
