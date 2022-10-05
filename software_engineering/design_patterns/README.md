[Home](../../README.md) >> [Software Engineering](../../README.md#software-engineering) >> [Design Patterns](./README.md)

# Design Patterns by [Erich Gamma](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Erich+Gamma&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLGMi5PScrVkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixaxcrsWZSZnKLgn5uYm7mBl3MXOxMEIAOIl3rVLAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAHoECFgQAg), [Richard Helm](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Richard+Helm&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLHMknNzcrVkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixax8gRlJmckFqUoeKTm5O5gZdzFzsTBCAA0-B00TAAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoA3oECFgQBQ), [Ralph Johnson](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Ralph+Johnson+computer+scientist&stichttps://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=Ralph+Johnson+computer+scientist&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLEsjNPLU7RkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixaxKgUl5hRkKHjlZ-QV5-cpaCTn5xaUlqQWKRQnZ6bmlWQWl2juYGXcxc7EwQgAnbxn82IAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAnoECFgQBAk=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLEsjNPLU7RkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixaxKgUl5hRkKHjlZ-QV5-cpaCTn5xaUlqQWKRQnZ6bmlWQWl2juYGXcxc7EwQgAnbxn82IAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAnoECFgQBA) & [John Vlissides](https://www.google.com/search?newwindow=1&rlz=1C5CHFA_enUS983US983&sxsrf=ALiCzsaB_94pXs0S2sz9_nRSbqncpjaWxA:1664738898246&q=John+Vlissides&stick=H4sIAAAAAAAAAOPgE-LQz9U3SDIyLFDiBLEszMvKjLRkspOt9JPy87P1y4syS0pS8-LL84uyrRJLSzLyixax8nnlZ-QphOVkFhdnpqQW72Bl3MXOxMEIAKer1XpOAAAA&sa=X&ved=2ahUKEwi1u7HVo8L6AhWOEFkFHebgAUEQmxMoAXoECFgQAw)

**Design patterns should not be applied indiscriminately. Often they achieve flexibility and variability by introducing additional levels of indirection, and that can complicate a design and/or cost you some performance.**

One thing expert designers know *not* to do is solve every problem from first principles. Rather, they reuse solutions that have worked for them in the past. To reuse the design, we must also record the decisions, alternatives, and trade-offs that led to it.

An **object** packs both data and the procedures (methods or operations) that operate on that data, an object performs an operation when it receives a **request** (or **message**) from a **client**. Requests are the *only* way to get an object to execute an operation, operations are the *only* way to change an object's internal data.

An object's *class* defines its implementation, an object's *type* defines its interface. They are not the same. Class (implementation) inheritance is discouraged, type (interface) inheritance is encouraged (also called **subtyping**). **Favor object composition over class inheritance,** designers often overuse inheritance as a reuse technique.

An object-oriented program's run-time structure often bears little resemblance to its code structure.

The hard part about object-oriented design is decomposing a system into objects (due to trade-offs), and there will always be disagreement on which approach is best.

## Common Causes of Redesign

| Mistake                                      | Downside                                     | Patterns to Rescue                                                                                                                                                      |
|----------------------------------------------|----------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Creating obj by specifying class explicitly. | Commits to class impl.                       | [Abstract Factory](patterns/p01_abstract_factory), [~~Factory Method~~](), [~~Prototype~~]()                                                                            |
| Dependence on specific operations.           | Commit to one way of satisfying a request.   | [~~Change of Responsibility~~](), [~~Command~~]()                                                                                                                       |
| Dependence on hardware/software platform.    | Obvious.                                     | [Abstract Factory](patterns/p01_abstract_factory), [~~Bridge~~]()                                                                                                       |
| Dependence on obj representations or impl.   | Client write code that depends on it.        | [Abstract Factory](patterns/p01_abstract_factory), [~~Bridge~~](), [~~Memento~~](), [~~Proxy~~]()                                                                       |
| Algorithm dependencies.                      | Algorithms are likely to evolve/change.      | [~~Builder~~](), [~~Iterator~~](), [~~Strategy~~](), [~~Template Method~~](), [~~Visitor~~]()                                                                           |
| Tight coupling.                              | Leads to monolithic systems.                 | [Abstract Factory](patterns/p01_abstract_factory), [~~Bridge~~](), [~~Chain of Responsibility~~](), [~~Command~~](), [~~Facade~~](), [~~Mediator~~](), [~~Observer~~]() |
| Extending functionality by subclassing.      | Explosion of classes, and (too) many others. | [~~Bridge~~](), [~~Chain of Responsibility~~](), [Composite](patterns/p08_composite), [~~Decorator~~](), [~~Observer~~](), [~~Strategy~~]()                             |
| Inability to alter classes conviniently.     | Often the case with commercial libraries.    | [~~Adapter~~](), [~~Decorator~~](), [~~Visitor~~]()                                                                                                                     |

## Table of Contents

| Purpose        | Design Pattern                                    | Aspects That Can Vary                                                                      |
|----------------|---------------------------------------------------|--------------------------------------------------------------------------------------------|
| **Creational** | [Abstract Factory](patterns/p01_abstract_factory) | families of product objects                                                                |
|                | [~~Builder~~]()                                   | how a composite object gets created                                                        |
|                | [~~Factory Method~~]()                            | subclass of object that is instantiated                                                    |
|                | [~~Prototype~~]()                                 | class of object that is instantiated                                                       |
|                | [~~Singleton~~]()                                 | the sole instance of  a class                                                              |
| **Structural** | [~~Adapter~~]()                                   | interface to an object                                                                     |
|                | [~~Bridge~~]()                                    | implementation of an object                                                                |
|                | [Composite](patterns/p08_composite)               | structure and composition of an object                                                     |
|                | [~~Decorator~~]()                                 | responsibilities of an object without subclassing                                          |
|                | [~~Facade~~]()                                    | interface to a subsystem                                                                   |
|                | [~~Flyweight~~]()                                 | storage costs of objects                                                                   |
|                | [~~Proxy~~]()                                     | how an object is accessed; its location                                                    |
| **Behaviroal** | [~~Chan of Responsibility~~]()                    | object that can fulfill a request                                                          |
|                | [~~Command~~]()                                   | when and how a request is fulfilled                                                        |
|                | [~~Interpreter~~]()                               | grammar and interpretation of a language                                                   |
|                | [~~Iterator~~]()                                  | how an aggregate's elements are accessed, traversed                                        |
|                | [~~Mediator~~]()                                  | how and which objects interact with each other                                             |
|                | [~~Memento~~]()                                   | what private information is stored outside an object, and when                             |
|                | [~~Observer~~]()                                  | number of objects that depend on another object; how the dependent objects stay up to date |
|                | [~~State~~]()                                     | states of an object                                                                        |
|                | [~~Strategy~~]()                                  | an algorithm                                                                               |
|                | [~~Template Method~~]()                           | steps of an algorithm                                                                      |
|                | [~~Visitor~~]()                                   | operations that can be applied to object(s) without changing their class(es)               |
