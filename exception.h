#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>
#include <exception>

class InvalidKey : public std::exception {}; 

class InvalidNode : public std::exception {};

class NoKeyFounded : public std::exception {};

#endif // EXCEPTION_H_