//Julian berhges 
// C++ parallel using OMP 


#include <iostream>
#include <vector> 
#include <omp.h> 


// parallel = opens the restaurant, all waiters (threads) come in
// single   = one waiter takes the first order
// task     = that order gets split into jobs any waiter can handle
// taskwait = don't serve the table until ALL dishes are ready

using namespace std;


    void insertion_sort(vector<int> & nums){
        int curr;
        int prev;


        for(int i =1; i<nums.size();i++){ // iteration of the whole array 
            curr= nums[i]; 
            prev = i-1;

            while (prev >=0 && nums[prev]>curr){ // while prev is >= 0 AND the number in prev is > than curr
                nums[prev+1]= nums[prev]; // aqui hace la copia del valor anterior el curr
                prev--; // prev= prev-1 
            
        }
        nums[prev+1]=curr;

        } 
    }


    void merge(vector<int> & nums, int left, int mid, int right){
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector <int>  L(n1);
        vector <int>  R(n2);

        for (int i = 0; i < n1; i++){   // i pq son dos distintas entonces da igual q pongaas i y j solo con i basta
            L[i] = nums[left + i];
        }
        for (int i = 0; i < n2; i++){
            R[i] = nums[mid + 1 + i];
        }   

        int i = 0;
        int j = 0; 
        int k = left;
        
        while (i<n1 && j <n2){

            if (L[i] <= R[j]) {   // esto compara los temp vectors y los ordena en el vector k. 
                nums[k] = L[i];
                i++;
            }
            else {
                nums[k] = R[j];
                j++;
            }
            k++;
        }


        while (i < n1) {    // este while es para los faltantes de los vectores, este es del vector i 
                nums[k] = L[i];
                i++;
                k++;
        }


            while (j < n2) { // este es del vector j 
                nums[k] = R[j];
                j++;    
                k++;
        }

        };



    void merge_sort(vector <int> &nums, int left , int right){
        if (left >= right)
        return;

        double mid = (left+right)/2; // o puedes usar; left +(right-left)/2 es lo mismo 

        merge_sort(nums, left, mid); //left side 
        merge_sort(nums,mid+1,right); // right side, es mid + 1 pq la parte derecha es despues del mid asi que solo seri mid +1
        merge(nums,left,mid,right);


    }



    void hybrid_sort (vector<int> &nums, int left , int right){
        if (right - left < 100){
            
        int curr;
        int prev;


        for(int i =left +1; i<= right;i++){ // iteration of the whole array 
            curr= nums[i]; 
            prev = i-1;

            while (prev >= left && nums[prev]>curr){ // while prev is >= 0 AND the number in prev is > than curr
                nums[prev+1]= nums[prev]; // aqui hace la copia del valor anterior el curr
                prev--; // prev= prev-1 
            
        }
        nums[prev+1]=curr;
        } 
        return;
    }

    double mid = (left+right)/2;

    #pragma omp task shared(nums)
    hybrid_sort(nums, left, mid);

    #pragma omp task shared(nums)
    hybrid_sort(nums, mid + 1, right);

    #pragma omp taskwait
    merge(nums, left, mid, right);


    }
    void print(vector<int> & nums){

        for( int i : nums)
        cout<< i <<" ";
        cout<< endl;

    }

int main(){

    vector <int> nums = {28472,1, 19, 58291, 1001, 764, 93022, 7, 44144, 120, 9999,
    38475, 55, 6721, 808, 1000001, 46, 314159, 73, 90210, 12321,
    6006, 891, 42, 757, 4884, 932, 11011, 2048, 5005, 12345,
    617, 909, 30003, 88, 1562, 76567, 101, 23432, 9701, 444,
    27364, 66, 78987, 321, 600, 1111, 4920, 8008, 13, 54345,
    71, 10001, 654, 45654, 999, 24680, 121, 90909, 37, 17371,
    202, 91827, 747, 3003, 57, 22222, 678, 15951, 404, 1110111,
    82, 70307, 11, 13531, 8624, 9009, 25, 98789, 606, 14541,
    300, 8888, 53, 74147, 16, 110010, 567, 29092, 77, 10101,
    212, 10010, 694, 777, 18381, 80808, 90, 3333, 272, 61516,
    707, 4096, 12821, 95, 21212, 818, 505, 99999, 462, 333,
    20202, 17, 72327, 100, 7117, 55555, 982, 7447, 29, 616,
    12121, 43034, 81, 2020, 3113, 7007, 4004, 93639, 63, 85258,
    191, 27272, 875, 575, 1441, 36, 15551, 90809, 40404, 27,
    31213, 696, 100001, 989, 72027, 68, 9099, 545, 2121, 50505,
    70707, 86, 13131, 42024, 33333, 11211, 48384, 74, 929, 9991,
    56565, 10201, 484, 73737, 222, 8088, 4334, 17, 6446, 2345,
    595, 60006, 9669, 242, 111, 91219, 8080, 98989, 500, 979,
    45454, 2882, 919, 1771, 32123, 90009, 744, 123321, 64046, 515,
    2002, 414, 6776, 888, 44544, 303, 700, 5665, 987, 131,
    20102, 434, 40004, 9898, 75057, 51515, 424, 1661, 30303, 525,
    69696, 800, 2772, 8118, 666, 9876, 7227, 4444, 112233, 99099,
    848, 1234321, 91919, 24242, 565, 640, 17771, 89098, 75757, 3223,
    878, 2012, 6336, 4567, 2442, 87678, 900, 6116, 313, 13579,
    24842, 2222, 67776, 50005, 1234, 9090, 8998, 454, 27772, 86468,
    767, 100000, 33633, 7337, 14941, 6666, 80008, 92929, 3443, 181,
    26262, 990, 112211, 54545, 66166, 488, 4545, 21212, 3123, 87878,
    2424, 4554, 70007, 88888, 912, 420, 34543, 9890, 232, 59095,
    1331, 72227, 3553, 98999, 585, 74447, 290, 102, 3883, 81818,
    123, 7007, 5555, 90109, 77477, 969, 500005, 282, 1010, 73337,
    4044, 65656, 14441, 808808, 474, 6226, 42424, 19191, 876, 35553,
    909909, 787, 20002, 2345432, 9191, 4040404, 58585, 656, 67876, 97979,
    3030, 31113, 61616, 74747, 5050, 81018, 96969, 909, 24042, 7117,
    383, 222222, 10000001, 5445, 65456, 727, 144441, 9696, 101101, 8228,
    32323, 4567654, 818181, 8787, 300003, 959, 43434, 22202, 989898, 212,
    35353, 1000000001, 8765, 464, 6789, 24442, 13331, 100000000, 75457, 6161,
    28282, 94949, 797, 343, 800008, 272727, 7070, 678876, 919919, 3773,
    84848, 5005, 2662, 111111, 30003, 949, 969969, 37773, 626, 52525,
    848848, 73237, 171, 47474, 909090, 876543, 4242, 5775, 123456, 56665,
    2552, 3030303, 7557, 6996, 9559, 23432, 79797, 1001001, 15151, 6789876,
    9797, 1221, 654321, 1551, 888888, 244442, 43034, 34343, 90909, 8181,
    515515, 565656, 69996, 8008, 7000007, 355553, 12221, 4774, 31313, 96669,
    82828, 555, 919191, 12344321, 6886, 7575, 41414, 777777, 4884, 2222222,
    89898, 10001, 71117, 363, 999999, 27172, 7447447, 202202, 3210123, 656565,
    990099, 6000006, 1223221, 83238, 899998, 110011, 22022, 545545, 9099099, 312213,
    45654, 707707, 100000001, 8080808, 7337, 1010101, 3993, 987789, 7777, 654456,
    1212121, 3434343, 45554, 9669, 60006, 808, 765567, 989, 404404, 2000002,
    12321, 1110111, 98789, 78987, 456765, 55555, 44444, 33333, 22222, 11111,1000000009};
    int n = nums.size();
    cout<< "The vector before the merge sort "<<endl;
    print(nums);


    #pragma omp parallel
    #pragma omp single
    hybrid_sort(nums,0,n-1);

    cout<< "The vector after sort"<<endl;
    print(nums);


}
