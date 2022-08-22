# Software Engineering at Google

Software Engineering at Google by [Titus Winters](https://www.linkedin.com/in/tituswinters/), [Tom Manshreck](https://www.linkedin.com/in/thomas-manshreck-0111a11/) & [Hyrum Wright](https://www.linkedin.com/in/hyrum-wright-0905427/)

## Chapter 1. What is Software Engineering?

In software engineering, engineers need to be more concerned with the passage of time and the eventual need for change. Software engineering isn't (just) programming.

Important question: "What is the expected lifespan of your code?" The answer can vary roughly by a factor of 100,000. For example, mobile apps generally have much shorter lifespan than Linux kernel code.

It's programming if "clever" is a compliment, but it's software engineering if "clever" is an accusation.

### Hyrum's Law (The Law of Implicit Dependencies)

Given enough time and enough users, even the most innocuous change will break something.

Example: code relying on the randomization (or the lack-of) of hash-ordering.

### Why Not Just Aim for "Nothing Changes"?

Even when no mistake was made, the passage of time (newer libraries, library bugs, newer hardware, etc.) makes change valuable.

Change is not inherently good. We shouldn't change just for the sake of change. But we do need to be capable of change.

### Policies That Don't Scale

Does the amount of work our engineer must perform grows as a function of the size of the organization?

Does the work scale up with the size of the codebase?

A good engineering team should internalize changes themselves, instead of forcing the work onto consumers (e.g., providing backward-compatible updates instead of setting a deadline to stop supporting older API/library).
