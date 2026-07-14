# rusalka
C implementation of number sequence cipher as seen in Call of Duty: Black Ops as described in [this Steam forum post](https://steamcommunity.com/sharedfiles/filedetails/?id=2583087495).

---
## Explanation
In the world of "Black Ops", the Soviet Union decided to use encoded number sequences to communicate with sleeper agents in the U.S.

The first layer of encoding is nothing more than a alphanumeric mapping, e.g.:
```
A=0, B=1, C=2, ...
```

However, any text decoded like this would appear to be gibberish. That's because the decoded text was encrypted using a **running key cipher**, essentially a sort of Vigenère cipher where, instead of using a single word, we can use a phrase or even a whole paragraph, essentially an abnormally large key to encrypt the contents of the message. In the world of "Black Ops", messages were first encrypted using passages from John Fitzgerald Kennedy's book "Profiles in Courage".

Any book can be used to encode or decode a message.

## Decryption Pipeline
Let's take a look at an example. Here's an encoded number sequence:

```
Echelon 3 24 20 12 19 17 17 22 19 23 19 4 0 7 6 7 19 10 12 16 17 6 14 4 3
17 24 20 13 24 8 16 17 1 24 9 21 15 0 5 15 4 4 23 6 11 25 14 4 20 4 9 14 18
12 8 7 21 6 4 21 7 21 4 2 14 3 14 7 18 13 6 22 16 6 1 21 21 15 3 5 24 9 11
2 10 5 21 4 20 11 19 12 5 12 13 12 5 17 19 3 14 21 12 15 17 7 7 2 2 21 1 10
22 13 5
```

Let's discard the word "Echelon". That's just padding. Focus just on the numbers.

First, we take the **first number** of the sequence. That number represents the page of a book in which you can find the key used in the message's encryption. Page 3 of "Profiles in Courage" by J. F. Kennedy has the following passage:

>  "Walter Lippmann, after nearly half a century of careful observation, rendered in his recent book a harsh judgment both on the politician and the electorate:"

We strip down the key for whitespace, special characters, and convert all alphabetic characters to uppercase.

```
WALTERLIPPMANNAFTERNEARLYHALFACENTURYOFCAREFULOBSERVATIONSRENDEREDINHISRECENTBOOKAHARSHJUDGEMENTBOTHONTHEPOLITICIAN
```

Now, let's convert the remaining numbers into their alphabetic mappings:

```
YUMTRRWTXTEAHGHTKMQRGOEDRYUNYIQRBYJVPAFPEEXGLZOEUEJOSM IHVGEVHVECODOHSNGWQGBVVPDFYJLCKFVEULTMFMNMFRTDOVMPRHHCCVBKWNF
```

And finally, we apply the key to the text like in a Vigenère cipher. Decrypting this text gives us the following message:

```
CUBANALLIESAUTHORIZECONSTRUCTIONOFPERMANENTBROADCASTSTATION RUSALKAGULFOFMEXICOPROJECTNOVAINITIATEDAWAITINSTRUCTIONS
```

> "Cuban allies authorize construction of permanent broadcast station Rusalka. Gulf of Mexico. Project Nova Initiated. Await instructions."

Some context can be lost due to pack of punctuation and spaces, but it can be inferred. This process can be completely reversed in order to obtain encoded messages, as seen in the code present in `main.c`.
