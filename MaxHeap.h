#include<stdio.h>
#include<math.h>

template <typename T>
class MaxHeap{

	//data structure just to use when is necessary to use indexOfAll function
	struct array_size {
		int *array;
		int f_index;
		int size;
	};

   private:
      int m;
      int size;
		int space;
      T *data;

		/*
		*order orders the content of the array of the struct i from greater to lowest (bubble sort)
		*/
		// CAN BE IMPROVED
		void order(array_size *i){		
			int ver = 1, num;
			while (ver == 1){
				for(num = 0, ver = 0 ; num < i->f_index - 1; num++)
					if(i->array[num] < i->array[num + 1]){
						i->array[num] += i->array[num + 1];
						i->array[num + 1] = i->array[num] - i->array[num + 1];
						i->array[num] -= i->array[num + 1];
						ver = 1;
					}
			}


		}

      /*
      * indexOfAll returns all indexes where data is equal to value
      */
      void indexOfAll(T value, int begin_index, int level, array_size *i){
         for(int num = begin_index; num < begin_index + m && num < size; num++){
				if(begin_index == 0 && num >= 1)
					break;

            if(value == this->data[num]){
					if(i->f_index + 1 == i->size){
						i->array = (T *)realloc(i->array, (i->size + 100)*sizeof(T));
						i->size = i->size + 100;
					}
					i->array[i->f_index++] = num;
				}

				if(value <= this->data[num]){
					// CAN BE IMPROVED
               indexOfAll(value, num + (num - begin_index)*m + (pow(m, level - 1) - (num - begin_index + 1)) + 1, level + 1, i);
            }
         }
      }

		/*
		*	addItem adds n to data at index i
		*/
		void addItem(T n, int i){
			if(this->size == this->space)
				moreMem();
			int actual_index = i;
			while(actual_index != 0){
				int root_index = floor((actual_index - 1)/m);
				if(n < this->data[root_index])
					break;
				this->data[actual_index] = this->data[root_index];

				actual_index = root_index;
			}
			this->data[actual_index] = n;
			this->size++;
		}

		/*
		*	maxChild returns the index of greater child of certain root	
		*	(init_index is the index of first child of that root)
		*/
		int maxChild(int init_index){
			T max = this->data[init_index];
			int max_index = init_index;
			for(int num = init_index + 1; num < init_index + m && num < this->size; num++)
				if(this->data[num] > max){
					max = this->data[num];
					max_index = num;
				}
			return max_index;
		}

		/*
		* moreMem extends the size of data
		*/
		void moreMem(){
			space += 100;
			data = (T *) realloc(data, sizeof(T)*space);
		}

   public:
		/*
		* constructor
		*/
      MaxHeap(int m){
         this->m = m;
         size = 0;
			space = 0;
			data = (T *) malloc(0);
      }

		/*
      * returns all indexes where data is equal to value in order (from greatest to lowest)
      */
      int* indexOfAll(T value){
			array_size i = {(T *)malloc(10*sizeof(T)), 0, 10};
			indexOfAll(value, 0, 1, &i);
			order(&i);
         return i.array;
      }

      /*
      * getRoot returns the root of the heap (the largest data item)
      */
      T getRoot(){
			return this->data[0];
      }

		/*
      * getSize returs the size of the heap
      */
		int getSize(){
			return this->size;
		}

		/*
      * addItem adds n to data
      */
		void addItem(T n){
			addItem(n, this->size);
		}

		/*
      * removeAllItem returns 0 if it was impossible to remove r (case it doesn't exists) and 1 in other cases
      * removeAllItem remove all occurrences of r in data
		*/
		int removeAllItem(T r){
			array_size i = {(T *)malloc(10*sizeof(T)), 0, 10};
			indexOfAll(r, 0, 1, &i);
			order(&i);

			if(i.f_index == 0)
				return -1;
			for(int num = 0; num < i.f_index; num++){
				int root_index = i.array[num];
				while(root_index*m + 1 < this->size){
					int child_index = maxChild(root_index*m + 1);
					this->data[root_index] = this->data[child_index];
					root_index = child_index;
				}
				if (root_index + 1 < size){		//if there are more items next to root_index
					size--;
					addItem(data[size], root_index);
				}
				size--;
			}
		}

		
		/* TO BE DONE	(at least)
		*
		*	removeItem()
		*	sort() 
		*/


};