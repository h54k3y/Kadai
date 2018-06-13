def readNumber(line, index):
    number = 0
    flag = 0
    keta = 1
    while index < len(line) and (line[index].isdigit() or line[index] == '.'):
        if line[index] == '.':
            flag = 1
        else:
            number = number * 10 + int(line[index])
            if flag == 1:
                keta *= 0.1
        index += 1
    token = {'type': 'NUMBER', 'number': number * keta}
    return token, index


def readPlus(line, index):
    token = {'type': 'PLUS'}
    return token, index + 1


def readMinus(line, index):
    token = {'type': 'MINUS'}
    return token, index + 1

def readMulti(line, index):
    token = {'type': 'MULTI'}
    return token, index + 1

def readDev(line, index):
    token = {'type': 'DEV'}
    return token, index + 1

def Bracket(line):
    index = 0
    while index < len(line) :
        if line[index] == '(':
            line = line.replace('(', '', 1)
            cnt = len(line) - 1
            while  cnt > index :
                if line[cnt] == ')':
                    line_bracket = line[index:cnt]
                    in_bracket = Calculator(line_bracket)
                    line_insert = str(in_bracket) 
                    line_replace = line_bracket + ')'
                    line = line.replace(line_replace, line_insert, 1)
                    return line
                cnt -= 1
        index += 1
    return line
    

def tokenize(line):
    tokens = []
    index = 0
    while index < len(line):
        if line[index].isdigit():
            (token, index) = readNumber(line, index)
        elif line[index] == '+':
            (token, index) = readPlus(line, index)
        elif line[index] == '-':
            (token, index) = readMinus(line, index)
        elif line[index] == '*':
            (token, index) = readMulti(line, index)
        elif line[index] == '/':
            (token, index) = readDev(line, index)
        else:
            print 'Invalid character found: ' + line[index]
            exit(1)
        tokens.append(token)
    return tokens


def evaluate(tokens):
    answer = 0
    tokens.insert(0, {'type': 'PLUS'}) # Insert a dummy '+' token
    index = 1
    while index < len(tokens) - 1:
        if tokens[index + 1]['type'] == 'MULTI' or tokens[index + 1]['type'] == 'DEV':
            pre_answer = tokens[index]['number']
            tokens[index]['number'] = 0
            while index < len(tokens):
                if index == len(tokens) - 1 :
                    tokens[index]['number'] = pre_answer
                    break;
                elif tokens[index]['type'] == 'NUMBER':
                    if tokens[index + 1]['type'] == 'MULTI':
                        pre_answer *= tokens[index + 2]['number']
                    elif tokens[index + 1]['type'] == 'DEV':
                        pre_answer /= float(tokens[index + 2]['number'])
                    elif tokens[index + 1]['type'] == 'MINUS' or tokens[index + 1]['type'] == 'PLUS':
                        tokens[index]['number'] = pre_answer
                        break;
                    else:
                        print 'Invalid syntax'
                    tokens[index + 1]['type'] = 'PLUS'
                    tokens[index + 2]['number'] = 0
                index += 1
        index += 1
    index = 1
    while index < len(tokens):
        if tokens[index]['type'] == 'NUMBER':
            if tokens[index - 1]['type'] == 'PLUS':
                answer += tokens[index]['number']
            elif tokens[index - 1]['type'] == 'MINUS':
                answer -= tokens[index]['number']
            elif tokens[index - 1]['type'] == 'MULTI' or tokens[index - 1]['type'] == 'DEV':
                    print 'Calculating PLUS and MINUS'
            else:
                print 'Invalid syntax'
        index += 1
    return answer

def Calculator(line):
    line = Bracket(line)
    tokens = tokenize(line)
    answer = evaluate(tokens)
    return answer

def test(line, expectedAnswer):
    actualAnswer = Calculator(line)
    if abs(actualAnswer - expectedAnswer) < 1e-8:
        print "PASS! (%s = %f)" % (line, expectedAnswer)
    else:
        print "FAIL! (%s should be %f but was %f)" % (line, expectedAnswer, actualAnswer)


# Add more tests to this function :)
def runTest():
    print "==== Test started! ===="
    test("1+2", 3)
    test("1.0+2.1-3", 0.1)
    test("4*3+2", 14)
    test("4.3/1", 4.3)
    test("4/2", 2)
    test("12*4", 48)
    test("6*12/3+12*4", 72)
    test("2+(2+3)", 7)
    test("3+(3*4+(3+2))", 20)
    test("2+3*(4+(1+2))", 23)
    test("42/(2*(1+(1+2)+3))", 3)
    print "==== Test finished! ====\n"

runTest()

while True:
    print '> ',
    line = raw_input()
    answer = Calculator(line)
    print "answer = %f\n" % answer