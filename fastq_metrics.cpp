#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <boost/iostreams/filtering_stream.hpp>

#include <iomanip>
#include <math.h>
using namespace std;

#define QUALITY_OFFSET 33

// https://stackoverflow.com/questions/29028137/how-to-multithread-reading-a-file-in-c11

int main(int argc, char* argv[])
{

    cout.setf(ios::fixed);
    string line, second, output;

    int qual;
    long read_size=0;
    long count_reads=0;
    long count_q30_bases=0;
    long count_q30_reads=0;
    long sum_read_scores=0;
    long total_sum_read_scores=0;
    double average_read_scores=0;
    long sum_scores=0;
    long total_bases=0;

    std::ifstream fastq_f(argv[1], std::ios_base::in | std::ios_base::binary);
    
    output = argv[1];
    unsigned found = output.find_last_of("/\\");
    output = argv[2] + output.substr(found + 1) + ".metrics.csv";

    std::ofstream results_f(output.c_str(), std::ios_base::out);
    
    boost::iostreams::filtering_istream in;
    
    in.push(fastq_f);

    clock_t begin = clock();

    //get reads size
    getline(in, line);
    getline(in, second);

    read_size = second.size();
    
    cout << "Read Size: " << read_size << endl;
    //read_size = 150;

    int n_content[read_size];
    for (int i = 0; i < read_size; i++) n_content[i] = 0;

    getline(in, line);
    getline(in, line);

    //do it for the first read first cause we can't go back to begining of the loop
    count_reads += 1;
    sum_read_scores=0;

    for(int i=0; i < read_size; ++i){

            char base = second[i];

            if (base == 'N' || base == 'n'){
                n_content[i] += 1;
            }

            qual = int(line[i]) - QUALITY_OFFSET;
            sum_scores += qual;
            //per read Q30
            sum_read_scores +=qual;
            //per base Q30
            if (qual >= 30){
                count_q30_bases += 1;
            }
        }
        average_read_scores = sum_read_scores/float(read_size);

        total_sum_read_scores += average_read_scores;

        if (average_read_scores >= 30){
                count_q30_reads += 1;
        }


    while(getline(in, line) && getline(in, second) && getline(in, line) && getline(in, line)) {
        
        count_reads += 1;
        sum_read_scores=0;
        read_size = second.size();

        for(int i=0; i <read_size; ++i){
            
            char base = second[i];

            if (base == 'N' || base == 'n'){
                n_content[i] += 1;
            }
            qual = int(line[i]) - QUALITY_OFFSET;
            // cout << "Qual: " << qual << endl;
            //per read Q30
            sum_read_scores +=qual;
            //per base Q30
            sum_scores += qual;
            if (qual >= 30){
                count_q30_bases += 1;
            }
        }
        average_read_scores = sum_read_scores/float(read_size);
        // cout << "Read Qual: " << qual << endl;
        total_sum_read_scores += average_read_scores;

        if (average_read_scores >= 30){
                count_q30_reads += 1;
        }
    }

    total_bases = read_size*count_reads;

    clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout << "Total Sum of Phred Scores: " << sum_scores << endl;
    cout << "Total number of Q30 Bases with phred quality score higher or equal than 30: " << count_q30_bases << endl;
    cout << "Total number of Bases: " << total_bases << endl;
    cout << "Total number of Reads with phred quality score higher or equal than 30: " << count_q30_reads << endl;
    cout << "Total number of Reads: " << count_reads << endl;
    cout << "Max per base N content: ";
    for (int i = 0; i < read_size; i++) {
        cout << (float(n_content[i]) / float(count_reads)) * 100;
        if (i < read_size-1) {
            cout << ',';
        }
    }
    cout << endl;
    cout << "------------------ Summary ------------------" << endl;
    cout << "Percentage of bases with phred quality score higher or equal than 30: " << (count_q30_bases/float(total_bases)) * 100 << endl;
    cout << "Percentage of reads with phred quality score higher or equal than 30: " << (count_q30_reads/float(count_reads)) * 100 << endl;
    cout << "Average per base quality Score: " << sum_scores/float(total_bases) << endl;
    cout << "Average per read quality Score: " << total_sum_read_scores/float(count_reads) << endl;
    
    cout << endl;
    cout << "Time Taken: " << elapsed_secs << endl;
    
    results_f << "sum_phred_scores," << sum_scores << endl;
    results_f << "count_q30_bases," << count_q30_bases << endl;
    results_f << "n_bases," << total_bases << endl;
    results_f << "count_q30_reads," << count_q30_reads << endl;
    results_f << "n_reads," << count_reads << endl;
    results_f << "max_percentage_per_base_n_content,";


    for (int i = 0; i < read_size; i++) {
        results_f << (float(n_content[i]) / float(count_reads)) * 100;
        if (i < read_size-1) {
            results_f << ',';
        }
    }
    results_f << endl;

    results_f << "percentage_q30_bases," << (count_q30_bases/float(total_bases)) * 100 << endl;
    results_f << "percentage_q30_reads," << (count_q30_reads/float(count_reads)) * 100 << endl;
    results_f << "average_bases_quality_score," << sum_scores/float(total_bases) << endl;
    results_f << "average_reads_quality_score," << total_sum_read_scores/float(count_reads) << endl;

    results_f << "time_taken," << elapsed_secs << endl;
    results_f.close();

}
