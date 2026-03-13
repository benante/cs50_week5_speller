**Note**
> Full details of the problem set are in the <a href="https://cs50.harvard.edu/x/psets/5/speller/">link here</a>.
> 
> Get distribution code here: <code>wget https://cdn.cs50.net/2026/x/psets/5/speller.zip</code>


# Speller

For this problem, you’ll implement a program that spell-checks a file, using a hash table.

## Background

Theoretically, on input of size n, an algorithm with a running time of n is “asymptotically equivalent,” in terms of O, to an algorithm with a running time of 2n. Indeed, when describing the running time of an algorithm, we typically focus on the dominant (i.e., most impactful) term (i.e., n in this case, since n could be much larger than 2). In the real world, though, the fact of the matter is that 2n feels twice as slow as n.

The challenge ahead of you is to implement the fastest spell checker you can! By “fastest,” though, we’re talking actual “wall-clock,” not asymptotic, time.
In <code>speller.c</code>, we've put together a program that's designed to spell-check a file after loading a dictionary of words from disk into memory. That dictionary, meanwhile, is implemented in a file called <code>dictionary.c</code>. (It could just be implemented in <code>speller.c</code>, but as programs get more complex, it's often convenient to break them into multiple files.) The prototypes for the functions therein, meanwhile, are defined not in <code>dictionary.c</code> itself but in <code>dictionary.h</code> instead. That way, both <code>speller.c</code> and <code>dictionary.c</code> can <code>#include</code> the file. Unfortunately, we didn't quite get around to implementing the loading part. Or the checking part. Both (and a bit more) we leave to you! 

### Understanding

**<code>dictionary.c</code>**
...Now open up <code>dictionary.c</code>. Notice how, atop the file, we've defined a <code>struct</code> called <code>node</code> that represents a node in a hash table. And we've declared a global pointer array, <code>table</code>, which will (soon) represent the hash table you will use to keep track of words in the dictionary. The array contains <code>N</code> node pointers, and we've set <code>N</code> equal to <code>26</code> for now, to match with the default <code>hash</code> function as described below. You will likely want to increase this depending on your own implementation of <code>hash</code>.
Next, notice that we've implemented <code>load</code>, <code>check</code>, <code>size</code>, and <code>unload</code>, but only barely, just enough for the code to compile. Notice too that we've implemented <code>hash</code> with a sample algorithm based on the first letter of the word. Your job, ultimately, is to re-implement those functions as cleverly as possible so that this spell checker works as advertised. And fast!

### Specification
Alright, the challenge now before you is to implement, in order, <code>load</code>, <code>hash</code>, <code>size</code>, <code>check</code>, and <code>unload</code> as efficiently as possible using a hash table in such a way that <code>TIME IN load</code>, <code>TIME IN check</code>, <code>TIME IN size</code>, and <code>TIME IN unload</code> are all minimized. To be sure, it's not obvious what it even means to be minimized, inasmuch as these benchmarks will certainly vary as you feed <code>speller</code> different values for <code>dictionary</code> and for <code>text</code>. But therein lies the challenge, if not the fun, of this problem. This problem is your chance to design. Although we invite you to minimize space, your ultimate enemy is time. But before you dive in, some specifications from us.

<ul>
  <li>You may not alter <code>speller.c</code> or <code>Makefile</code>.</li>
  <li>You may alter <code>dictionary.c</code> (and, in fact, must in order to complete the implementations of <code>load</code>, <code>hash</code>, <code>size</code>, <code>check</code>, and <code>unload</code>), but you may not alter the declarations (i.e., prototypes) of <code>load</code>, <code>hash</code>, <code>size</code>, <code>check</code>, or <code>unload</code>. You may, though, add new functions and (local or global) variables to <code>dictionary.c</code>.</li>
  <li>
You may change the value of <code>N</code> in <code>dictionary.c</code>, so that your hash table can have more buckets.
    
  </li>
  <li>
You may alter <code>dictionary.h</code>, but you may not alter the declarations of <code>load</code>, <code>hash</code>, <code>size</code>, <code>check</code>, or <code>unload</code>.
    
  </li>
  <li>
Your implementation of <code>check</code> must be case-insensitive. In other words, if <code>foo</code> is in dictionary, then <code>check</code> should return true given any capitalization thereof; none of <code>foo</code>, <code>foO</code>, <code>fOo</code>, <code>fOO</code>, <code>fOO</code>, <code>Foo</code>, <code>FoO</code>, <code>FOo</code>, and <code>FOO</code> should be considered misspelled.
    
  </li>
  <li>
Capitalization aside, your implementation of <code>check</code> should only return <code>true</code> for words actually in <code>dictionary</code>. Beware hard-coding common words (e.g., <code>the</code>), lest we pass your implementation a <code>dictionary</code> without those same words. Moreover, the only possessives allowed are those actually in <code>dictionary</code>. In other words, even if <code>foo</code> is in <code>dictionary</code>, <code>check</code> should return <code>false</code> given <code>foo's</code> if <code>foo's</code> is not also in <code>dictionary</code>.
    
  </li>
  <li>
You may assume that any <code>dictionary</code> passed to your program will be structured exactly like ours, alphabetically sorted from top to bottom with one word per line, each of which ends with <code>\n</code>. You may also assume that <code>dictionary</code> will contain at least one word, that no word will be longer than <code>LENGTH</code> (a constant defined in <code>dictionary.h</code>) characters, that no word will appear more than once, that each word will contain only lowercase alphabetical characters and possibly apostrophes, and that no word will start with an apostrophe.
    
  </li>
  <li>
You may assume that <code>check</code> will only be passed words that contain (uppercase or lowercase) alphabetical characters and possibly apostrophes.
    
  </li>
  <li>
Your spell checker may only take <code>text</code> and, optionally, <code>dictionary</code> as input. Although you might be inclined (particularly if among those more comfortable) to "pre-process" our default dictionary in order to derive an "ideal hash function" for it, you may not save the output of any such pre-processing to disk in order to load it back into memory on subsequent runs of your spell checker in order to gain an advantage.
    
  </li>
  <li>
Your spell checker must not leak any memory. Be sure to check for leaks with <code>valgrind</code>.
    
  </li>
  <li>
The hash function you write should ultimately be your own, not one you search for online.
    
  </li>
  
</ul>


