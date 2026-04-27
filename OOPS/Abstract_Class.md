## Abstract Class vs Interface (VERY IMPORTANT)
#### Abstract Class
Can have:
Pure virtual functions
Normal functions
Member variables

#### Interface - pure contract
Only pure virtual functions
No state (ideally) i.e An interface should not store data (member variables) — only define behavior.

#### Points to remember
Used heavily in LLD for loose coupling as we can swap implementations without changing other code.

We can't create objects of abstract classes.