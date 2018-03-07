#include "iterator.h"

//OperatorIterator
void OperatorIterator::first(){
    current_ptr = this-> self_ptr -> get_left();
}
void OperatorIterator::next(){
    // current_ptr = this -> self_ptr -> get_left();
    if(current_ptr == self_ptr -> get_left()){
        current_ptr = self_ptr -> get_right();
    }
    else{
        current_ptr = NULL;
    }
    
}
bool OperatorIterator::is_done(){
    return (current_ptr == NULL);
}
Base* OperatorIterator::current(){
    return current_ptr;
}

//UnaryIterator
void UnaryIterator::first(){
    current_ptr = self_ptr -> get_left();
}
void UnaryIterator::next(){
    current_ptr = NULL;
}
bool UnaryIterator::is_done(){
    return (current_ptr == NULL);
}
Base* UnaryIterator::current(){
    return current_ptr;
}

//NullIterator
void NullIterator::first(){};
void NullIterator::next(){};
bool NullIterator::is_done(){
    return true;
}
Base* NullIterator::current(){
    return NULL;
}


//PreorderIterator
void PreorderIterator::first() {
    // Empty the stack (just in case we had something leftover from another run)
    // Create an iterator for the Base* that we built the iterator for
    // Initialize that iterator and push it onto the stack
    Iterator* iter = this->self_ptr->create_iterator();
    if (iter) {
        iter->returnSelfPtr()->print();
        cout << endl;
        iter->first();
        while (!iterators.empty()) {
            iterators.pop();
            //potential memory leak
        }
        iterators.push(iter);
    }
}
void PreorderIterator::next() {
    // Create an iterator for the item on the top of the stack
    Iterator* iter = iterators.top()->current()->create_iterator();
    // Initialize the iterator and push it onto the stack
    // As long as the top iterator on the stack is_done(), pop it off the stack and then advance whatever iterator is now on top of the stack
    iter->first();
    iterators.push(iter);
    while (iterators.size() > 0 &&  iterators.top()->is_done()) {
		//delete iterators.top();
		iterators.pop();
		if (iterators.size() > 0) {
		    iterators.top()->next();
		}
	}
}

bool PreorderIterator::is_done() {
    // Return true if there are no more elements on the stack to iterate
    return !(iterators.size());
}

Base* PreorderIterator::current() {
    // Return the current for the top iterator in the stack
    if (this->iterators.size() > 0) {
		return this->iterators.top()->current();
	} else {
		return NULL;
	}
}


