
#include "queue.h"
#include <algorithm>

void queue::checkinvariant( ) const
{
   if( current_capacity < 2 )
   {
      std::cout << "current capacity < 2\n";
      printstate( std::cout );
      std::abort( );
   }

   if( current_size > current_capacity )
   {
      std::cout << "current_size > current_capacity\n";
      printstate( std::cout );
      std::abort( );
   }

   if( current_front >= current_capacity )
   {
      std::cout << "current_front >= current_capacity\n";
      printstate( std::cout );
      std::abort( );
   }
}

void queue::printstate( std::ostream& out ) const
{
   size_t current_end = current_front + current_size;
   if( current_end >= current_capacity )
      current_end -= current_capacity;
   
   if( current_front + current_size < current_capacity )
   {
      for( size_t i = 0; i != current_front; ++ i )
         out << ".   ";
      out << "(front)   ";
      for( size_t i = current_front; i != current_end; ++ i )
         out << data[i] << "   ";
      for( size_t i = current_end; i != current_capacity; ++ i )
         out << ".   ";
   }
   else
   {
      for( size_t i = 0; i != current_end; ++ i )
         out << data[i] << "   ";
      for( size_t i = current_end; i != current_front; ++ i )
         out << "X   ";
      out << "(front)   ";
      for( size_t i = current_front; i != current_capacity; ++ i )
         out << data[i] << "   ";
   }
   out << "\n";
}


queue::queue( ) : current_capacity(4), current_front(), data(), current_size()
{ }


queue::valtype* queue::makecopy( size_t c ) const
{
   if( c < current_size )
      throw std::logic_error( "makecopy: c is too small" );

   valtype* newQueue = new valtype[c];
   if(current_front + current_size <= current_capacity)
      std:copy(&data[current_front], &data[current_front + current_size], newQueue)
   else{
      std::copy(&data[current_front], &data[current_capacity], newQueue);
      std::copy(data, &data[current_size + current_front - current_capacity], newQueue);
   }

   return newQueue;

}


void queue::ensure_capacity( size_t c )
{
   if(c <= current_capacity){return}
   size_t new_cap = current_capacity;
   else{
      while(new_cap < c){
         new_cap *= 2;
      }
      valtype* temp = makecopy(c);
      delete [] data;
      data = temp; 
      current_capacity = new_cap;
      current_front = 0;
   }
}
 

void queue::push( const valtype& val )
{
   ensure_capacity(current_size + 1);
   data[(current_front + current_size) % current_capacity] = val;
   current_size++;
}


void queue::pop( )
{ 
   if(current_size){
      current_front++;     
      current_front %= current_capacity;
      current_size--;
   }
   else
      throw std::logic_error( "pop: queue is empty" );
}


const queue::valtype& queue::peek( ) const
{ 
   if(current_size){
      return data[current_front];
   }
   else
      throw std::logic_error( "pop: queue is empty" );
}


queue::~queue( )
{ 
   delete [] data;
}



queue::queue( const queue& q )
{ 
   current_capacity = q.current_capacity;
   current_size = q.current_size;
   current_front = q.current_front;
   data = q.makecopy(q.current_capacity);
}


const queue& queue::operator = ( const queue& q )
{ 
   if(this != &q){
		current_size = q.current_size;
		current_front = 0;
		current_capacity = q.current_capacity;
		delete [] data;
		data = q.makecopy(q.current_capacity);
	}
	return *this;
   //gonna need some expl when back
}


void queue::print( std::ostream& out ) const
{ 
   if((current_front + current_size) < current_capacity){
      for(size_t i = current_front; i < (current_size + current_front); i++){
         if(i < current_front){
            out << ", ";
         }
         out << data[i];
      }
   }
   else{
      for(size_t i = current_front; i < current_capacity; i++){
         if(i > current_front){
            out << ", ";
         }
         out << data[i];
      }
      out << ", ";
      for(size_t i = 0; i < (current_front + current_size - current_capacity); i++){
         if(i > 0){
            out << ", ";
         }
         out << data[i];
      }
   }
}


void queue::clear( )
{ 
   current_front = 0;
   current_size = 0;
}


size_t queue::size( ) const
{ 
   return current_size;
}


bool queue::empty( ) const
{ 
   return if(!current_size);
}

queue::queue( std::initializer_list< valtype > values )
{ }


