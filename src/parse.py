import json
import sys

if __name__ == "__main__":
    final_string = ""
    args = []
    for arg in sys.argv[1:]:
        #print (arg)
        args.append(arg)

    js = json.loads(args[1])
    #print(js['description'])
    if js['description'].lower() != 'success' :
        final_string = "fail"
    else :
        final_string += js['description'] + "$"

        if js['transactions'] == [] :
            final_string = "empty"
        else :
            transactions = js['transactions']
            for t in transactions :
#                print(t)
                for sub_t in t :
#                    print(t[sub_t])
                    final_string += str(t[sub_t]) + ","
                final_string = final_string[:-1]
                final_string += "$"
            final_string = final_string[:-1]

#    print(final_string)
    f = open("/home/eos/contracts/IWC_DEV/log/parsed_json.txt", 'w')
    f.write(final_string)
    f.close()

    archive_string = args[0] + "@" + final_string + "\n"
    archive_f = open("/home/eos/contracts/IWC_DEV/log/archive_parsed.txt", 'a')
    archive_f.write(archive_string)
    archive_f.close()
