[Home](../../README.md) >> [Software Engineering](../../README.md#software-engineering) >> [Design Patterns](./README.md)

# Design Patterns by [Erich Gamma](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Erich+Gamma&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLGMi5PScrVkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixaxcrsWZSZnKLgn5uYm7mBl3MXOxMEIAOIl3rVLAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAHoECFgQAg), [Richard Helm](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Richard+Helm&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLHMknNzcrVkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixax8gRlJmckFqUoeKTm5O5gZdzFzsTBCAA0-B00TAAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoA3oECFgQBQ), [Ralph Johnson](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Ralph+Johnson+computer+scientist&stichttps://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Ralph+Johnson+computer+scientist&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLEsjNPLU7RkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixaxKgUl5hRkKHjlZ-QV5-cpaCTn5xaUlqQWKRQnZ6bmlWQWl2juYGXcxc7EwQgAnbxn82IAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAnoECFgQBAk=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLEsjNPLU7RkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixaxKgUl5hRkKHjlZ-QV5-cpaCTn5xaUlqQWKRQnZ6bmlWQWl2juYGXcxc7EwQgAnbxn82IAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAnoECFgQBA) & [John Vlissides](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=John+Vlissides&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLEszMvKjLRkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixax8nnlZ-QphOVkFhdnpqQW72Bl3MXOxMEIAKer1XpOAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAXoECFgQAw)



## Chapter 1. Introduction

One thing expert designers know *not* to do is solve every problem from first principles. Rather, they reuse solutions that have worked for them in the past.

To reuse the design, we must also record the decisions, alternatives, and trade-offs that led to it.

### 1.6 How Design Patterns Solve Design Problems

An **object** packs both data and the procedures (methods or operations) that operate on that data, an object performs an operation when it receives a **request** (or **message**) from a **client**.

Requests are the *only* way to get an object to execute an operation, operations are the *only* way to change an object's internal data.

**The hard part about object-oriented design is decomposing a system into objects** (due to trade-offs), and there will always be disagreement on which approach is best.

An object's *class* defines its implementation, an object's *type* defines its interface. They are not the same.

Class (implementation) inheritance is discouraged, type (interface) inheritance is encouraged (also called **subtyping**). **Favor object composition over class inheritance,** designers often overuse inheritance as a reuse technique.

An object-oriented program's run-time structure often bears little resemblance to its code structure.

#### Common Causes of Redesign

| Mistake                                      | Downside                                   | Patterns to Rescue                                                                                                 |
|----------------------------------------------|--------------------------------------------|--------------------------------------------------------------------------------------------------------------------|
| Creating obj by specifying class explicitly. | Commits to class impl.                     | [Abstract Factory](), [Factory Method](), [Prototype]()                                                            |
| Dependence on specific operations.           | Commit to one way of satisfying a request. | [Change of Responsibility](), [Command]()                                                                          |
| Dependence on hardware/software platform.    | Obvious.                                   | [Abstract Factory](), [Bridge]()                                                                                   |
| Dependence on obj representations or impl.   | Client write code that depends on it.      | [Abstract Factory](), [Bridge](), [Memento](), [Proxy]()                                                           |
| Algorithm dependencies.                      | Algorithms are likely to evolve/change.    | [Builder](), [Iterator](), [Strategy](), [Template Method](), [Visitor]()                                          |
| Tight coupling. | Leads to monolithic systems. | [Abstract Factory](), [Bridge](), [Chain of Responsibility](), [Command](), [Facade](), [Mediator](), [Observer]() |
| Extending functionality by subclassing. | Explosion of classes, and (too) many others. | [Bridge](), [Chain of Responsibility](), [Composite](), [Decorator](), [Observer](), [Strategy]()                  |
| Inability to alter classes conviniently. | Often the case with commercial libraries. | [Adapter](), [Decorator](), [Visitor]()                                                                            |
