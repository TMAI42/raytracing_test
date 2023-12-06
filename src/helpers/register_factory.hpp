//
// Created by tmai42 on 9/5/22.
//

// 69 totally unreadable lines, plz don`t even try...
// UPD: this was funny before documentation has been added
#ifndef REGISTER_FACTORY_HPP
#define REGISTER_FACTORY_HPP

#include <memory>
#include <string>
#include <unordered_map>

#include <cstdlib>
#include <cxxabi.h>

// Function taken from stackoverflow:
// https://stackoverflow.com/questions/281818/unmangling-the-result-of-stdtype-infoname/4541470#comment26629807_4541470
std::string demangle(const char *name) {
    int status = -4; // some arbitrary value to eliminate the compiler warning

    std::unique_ptr<char, void (*)(void *)> res{
            abi::__cxa_demangle(name, NULL, NULL, &status), std::free};

    return (status == 0) ? res.get() : name;
}

// Generic factory class for creating instances of derived classes.
// This template class facilitates the creation of objects without specifying
// the exact class type at compile time. It uses a registry pattern where derived
// classes are registered with a unique string identifier. When creating an object,
// this identifier is used to find and construct the appropriate instance.
template <class Base, class... Args>
class Factory {
public:

    // Factory method to create an instance of a registered class.
    // This method creates an object of a class registered with the factory. It expects
    // the class identifier as a string and forwards any additional arguments to the class constructor.
    template <class ... T>
    static std::unique_ptr<Base> make(const std::string &s, T&&... args) {
        return data().at(s)(std::forward<T>(args)...);
    }

    // Inner class for registering classes with the factory.
    // This structure is used by derived classes to register themselves with the factory.
    // It also ensures that the registration happens automatically before main() begins execution.
    template <class T>
    struct Registrar : Base {
        friend T;

        // Function to handle the registration process.
        // This static method registers a new class with the factory, associating it with a
        // demangled type name. The function is automatically called when the static `registered` member is initialized.
        static bool regisrterT() {
            const auto name = demangle(typeid(T).name());
            Factory::data()[name] = [](Args... args) -> std::unique_ptr<Base> {
                return std::make_unique<T>(std::forward<Args>(args)...);
            };
            return true;
        }
        static bool registered;

    private:
        // Private constructor to restrict instantiation.
        // This constructor is private and only accessible by the `Registrar` structure,
        // ensuring that only registered classes can be instantiated through the factory.
        Registrar() : Base(Key{}) { (void)registered; }
    };

    friend Base;

private:
    // Private inner class used as a key for access control.
    // This class is a part of the Factory's implementation to control access to certain constructors.
    class Key {
        Key(){};
        template <class T> friend struct Registrar;
    };

    // Alias for the function type used in the factory.
    // Defines the type for the function pointers stored in the factory's map.
    using FuncType = std::unique_ptr<Base> (*)(Args...);

    // Default constructor.
    Factory() = default;

    // Function to access the internal registry map.
    // This static method provides access to the map that stores the registered classes and their corresponding factory functions.
    static auto &data() {
        static std::unordered_map<std::string, FuncType> s;
        return s;
    }
};

// Static member initialization.
// This line ensures that the registration process for each class happens before the execution of main().
template <class Base, class... Args>
template <class T>
bool Factory<Base, Args...>::Registrar<T>::registered =
        Factory<Base, Args...>::Registrar<T>::registerT();

#endif // REGISTER_FACTORY_HPP