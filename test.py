def reformat_line(line):
    # Splitting by ': ' handles 'A:', 'F:', etc.
    # Splitting by ' ' handles 'SP:', 'PC:', etc.
    components = line.split(': ')
    components = [i.split(' ') for i in components]
    components = [item for sublist in components for item in sublist]
    line = ""
 
    for idx,i in enumerate(components):
        # print(idx)
        if idx % 2 == 0:
            # Handle the PC memory separately
            if components[idx] == "PC":
        
                pc_mem = components[2].strip().split(" ")
                pc_mem_formatted = ','.join(pc_mem)
                line += f"{components[idx]}:{components[idx + 1][3:]} PCMEM:{components[idx+2][1:]+',' + components[idx+3]+',' + components[idx+4]+',' + components[idx+5][:-2]}"
                break
               
            
            # Reformat other lines
            line += f"{components[idx]}:{components[idx + 1]} "
      
    return line

def main():
    with open("7.txt", "r") as infile, open("7e.log", "a") as outfile:
        for line in infile:
          
            outfile.write(reformat_line(line) + "\n")
            # exit(0)

if __name__ == "__main__":
    main()
