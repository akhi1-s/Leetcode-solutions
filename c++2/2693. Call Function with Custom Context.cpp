// Define the JSONValue type
type JSONValue =
    | null
    | boolean
    | number
    | string
    | JSONValue[]
    | { [key: string]: JSONValue };

// Extend the Function interface to include the callPolyfill method
interface Function {
    callPolyfill(context: Record<string, JSONValue>, ...args: JSONValue[]): JSONValue;
}

// Implement the callPolyfill method
Function.prototype.callPolyfill = function(
    context: Record<string, JSONValue>,
    ...args: JSONValue[]
): JSONValue {
    // Ensure the context is an object (even if null or primitive values are passed)
    const obj: Record<string | symbol, any> = Object(context);

    // Create a unique symbol to avoid overwriting existing properties in the context
    const fnSymbol: symbol = Symbol();

    // Assign the current function to the context object under the unique symbol key
    obj[fnSymbol] = this;

    // Call the function with the context and arguments, and store the result
    const result: JSONValue = obj[fnSymbol](...args);

    // Clean up: delete the temporary property from the context object
    delete obj[fnSymbol];

    // Return the result of the function call
    return result;
};
