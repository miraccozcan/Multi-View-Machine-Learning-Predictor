# Multi-View-Machine-Learning-Predictor
**SED505 Assignment 2**

## Output
![Output](https://i.ibb.co/xD9Z9B2/image.png)

## Language Choice: Why C/C++?
The assignment is required to be implemented in C/C++ due to:
1. **Memory and Performance**: C/C++ allows better control over memory and performance, which is important when running on small devices with limited resources.
2. **No Math Library**: The training model must work without using the standard math library. C/C++ makes it easier to create efficient math approximations like the Taylor Series directly.

### Why should this code be written in C/C++ only? Why not Java, C# or Python?
- **Java and C#**: Both are powerful, but they have more runtime overhead because of their managed environments (JVM or CLR). This can be a disadvantage for small, resource-limited devices.
- **Python**: It is easy to use and understand, but it is slower than compiled languages like C/C++. This makes it less suitable for performance-focused tasks.

## Name two other possible common usages for this design pattern.
1. **Event Handling in GUIs**: This pattern is useful for updating multiple parts of a program in response to user actions, like clicking a button.
2. **Real-Time Monitoring Systems**: It is used in dashboards or monitoring tools to update displays or logs whenever data changes.

## What might cause a test build to behave differently from a release build?
- **Debug Information**: Test builds usually include extra debug symbols and logging for development, which may change the program's behavior.
- **Optimization**: Release builds often have compiler optimizations turned on, making the code run faster but sometimes changing behavior, especially in timing-sensitive situations.

## Did you use interface classes for all components in this assignment? If not, why?
- **No**: Interface classes were used only for the views (`IView`) because they needed a consistent way to be attached to the `ModelTrainer` and receive updates. The `ModelTrainer` did not need an interface because it was the core logic and using an interface for it would not add significant benefits.
