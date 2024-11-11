# Multi-View-Machine-Learning-Predictor
**SED505 Assignment 4**  
Mirac Ozcan 181468216  
Paschal Ibeh 147295216

## Output
![Output](https://i.ibb.co/xD9Z9B2/image.png)

## UML Diagram
![UML](https://i.ibb.co/z5q0z30/image.png)

## Questions
### Language Choice: Why C/C++?
We used **C/C++** because:
1.  C/C++ allows better control over memory and performance.
2. The training model must work without using the standard math library. C/C++ makes it easier to create efficient math approximations.

### Why should this code be written in C/C++ only? Why not Java, C# or Python?
- **Java and C#**: They have more runtime overhead because of their managed environments
- **Python**: It is slower than compiled languages like C/C++

### Name two other possible common usages for this design pattern.
1. **Event Handling in GUIs**: This pattern is useful for updating multiple parts of a program in response to user actions, like clicking a button.
2. **Real-Time Monitoring Systems**: It is used in dashboards or monitoring tools to update displays or logs whenever data changes.

### What might cause a test build to behave differently from a release build?
- Test builds usually include extra debug symbols and logging for development, which may change the program's behaviour.
- Release builds often have compiler optimizations turned on, making the code run faster but sometimes changing behaviour, especially in timing-sensitive situations.

### Did you use interface classes for all components in this assignment? If not, why?
- **No**: Interface classes were used only for the views (`IView`) because they needed a consistent way to be attached to the `ModelTrainer` and receive updates. The `ModelTrainer` did not need an interface because it was the core logic and using an interface for it would not add significant benefits.

