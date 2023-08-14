// Real talk: I did not understand this challenge so I used ChatGPT to exlain it
// so that a smoothbrain like me can understand
// "Imagine you're riding a bike on a bumpy road. When you go over a bump, you
// feel how much the road is pushing against your bike. The numerical derivative
// is like figuring out how strong that push is by looking at how much your bike
// moves and how bumpy the road is right at that point. It helps us understand
// how things are changing when we move around on the bumpy road!"
// meh, okay... what are some real world uses?
// "Engineers use derivatives to design and optimize things. For instance, when
// designing a car's suspension, derivatives can help determine how the
// suspension system responds to bumps on the road."
// Okay that's pretty cool!
// It gave me this weird equation of sorts
// "finite difference approximation"
// "Derivative ≈ (F(x + h) - F(x - h)) / (2 * h)"
// Where `h` = "a small step to the right/left of the point `x`"
// "The smaller h is, the more accurate your approximation will be"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// First parameter is a function pointer
// Declared respecting the book's conventions
double f(double F(double), double x) {
    double const h = 0.0001;
    return (F(x + h) - F(x - h)) / (2 * h);
}

int main(void) {
    double x = 69;

    double derivative = f(cos, 69);
    printf("The derivative of cos at %g is %g\n", x, derivative);

    derivative = f(sin, 69);
    printf("The derivative of sin at %g is %g\n", x, derivative);

    derivative = f(sqrt, 69);
    printf("The derivative of sqrt at %g is %g\n", x, derivative);

    return EXIT_SUCCESS;
}
