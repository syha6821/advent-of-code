def read_report(filepath):
    with open(filepath,'r') as f:
        return f.read().split('\n')[:-1]

def oxygen_rating(report):
    def calc(report,index):
        if len(report) == 1:
            return report[0]
        else:
            ones = []
            zeros = []
            for bits in report:
                (ones if bits[index] == '1' else zeros).append(bits)
            return calc(ones if len(ones) >= len(zeros) else zeros,index+1)
    return int(calc(report,0),2)

def co2_rating(report):
    def calc(report,index):
        if len(report) == 1:
            return report[0]
        else:
            ones = []
            zeros = []
            for bits in report:
                (ones if bits[index] == '1' else zeros).append(bits)
            return calc(zeros if len(ones) >= len(zeros) else ones,index+1)
    return int(calc(report,0),2)

def solve(filepath):
    report = read_report(filepath)
    return oxygen_rating(report) * co2_rating(report)
