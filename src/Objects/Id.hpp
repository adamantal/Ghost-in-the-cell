#ifndef ID_HPP
#define ID_HPP

typedef unsigned int Id;

const Id DEFAULT_ID = 0;
const Id MIN_ID = DEFAULT_ID + 1;

Id nextId();

//TODO consider making a static next id method

#endif // ID_HPP
