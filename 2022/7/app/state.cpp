#include "state.h"

vector<int> sizes;

int get_dir_size(const Dir& dir)
{
    int sum_of_file_size = 0;
    for(const File& file : dir.get_sub_files())
    {
        sum_of_file_size += file.get_size();
    }

    int sum_of_dir_size = 0;
    
    for(const Dir& directory : dir.get_sub_dirs())
    {
        int dir_size = get_dir_size(directory);
        sum_of_dir_size += dir_size;
    }
    
    int sum = sum_of_dir_size + sum_of_file_size;
    cout << dir.get_name() << ':' << sum << '\n';
    sizes.push_back(sum);
    return sum;
}

int find_lowest_to_delete(const int needed, const int total)
{
    int lowest = total;
    cout << "init : " << lowest << '\n';
    for(int size : sizes)
    {
        if((size > needed) && (size < lowest)) lowest = size;
    }
    return lowest;
}