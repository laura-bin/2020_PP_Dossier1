#!/bin/bash
# find max line length (CSV_BUF_LEN)
# & each field max length

csv_field_length() {
    local file="$1"
    local field_length

    # count how many fields there are
    local field_count="$(head -1 "$file" | grep -o ';' | wc -l)"

    # for each line of the file, print the length of the nth field, then sort from high to low & take the first line
    # field 0 is the full line
    for i in $(seq 0 $(( $field_count + 1 ))); do
        # run awk with LC_ALL=C to avoid interpreting multibyte chars as single chars,
        # that will give the size needed for char arrays
        field_length="$(tail -n +2 "$file" | LC_ALL=C awk -F';' "{ print length(\$$i), \"-\", \$$i }" | sort -rn | head -1)"
        echo "field $i: $field_length"
    done
}

echo "Country table"
csv_field_length ../data_import/DB_Country.csv

echo "Job table"
csv_field_length ../data_import/DB_Job.csv

echo "Industry table"
csv_field_length ../data_import/DB_Industry.csv

echo "Group table"
csv_field_length ../data_import/DB_Group.csv

echo "Company table"
csv_field_length ../data_import/DB_Company.csv

echo "Person table"
csv_field_length ../data_import/DB_Person.csv
