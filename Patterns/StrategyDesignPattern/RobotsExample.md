#### Robot Design

Check example of Robots in image (robots.png)

Robot can choose strategy dynamically.

✅ Composition over inheritance
✅ Runtime polymorphism


We use Strategy to avoid hardcoding behavior in class hierarchy and instead delegate behavior to interchangeable components.

Inheritance reduction is a side effect, not the goal.

Other than robot example, example we have is Retry logic.

RetryStrategy can have FixedRetry, NoRetry and ExponentialBackoff.