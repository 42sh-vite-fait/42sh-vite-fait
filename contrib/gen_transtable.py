#!/usr/bin/env python3

import xml.etree.ElementTree as etree
from sys import argv

def list_from_tree(tree):
    elem_list = list(e.tag for e in tree)
    return elem_list

def print_error(state_dico):
    return '\n\t\t\tT({}),'.format(state_dico['error'])

def print_fallback(stack_tree, state_dico):
    if 'fallback' in stack_tree.attrib.keys():
        return '\n\t\t\tT({}),'.format(state_dico[stack_tree.attrib['fallback']])
    else:
        return print_error(state_dico)

def print_transition(symbol, stack_tree, state_dico, stack_state_dico):
    if stack_tree is None:
        return print_error(state_dico)

    symbol_elem = stack_tree.find(symbol)
    if symbol_elem is None:
        return print_fallback(stack_tree, state_dico)

#    print('ceci: {}, text = {}'.format(symbol_elem, symbol_elem.text))
#    print(state_dico, "\n")
    next_state = state_dico[symbol_elem.text]

    if 'push' in symbol_elem.attrib.keys():
        return '\n\t\t\tU({}, {}),'.format(next_state, stack_state_dico[symbol_elem.attrib['push']])
    elif 'pop' in symbol_elem.attrib.keys():
        return '\n\t\t\tO({}),'.format(next_state)
    else:
        return '\n\t\t\tT({}),'.format(next_state)
    

    '''
    symbol_elem = stack_tree.find(symbol) if stack_tree is not None else None
#   trans_fallback = stack_tree.attrib['fallback'] if stack_tree.attrib.keys().find('fallback') is not None else None
    next_state_txt = symbol_elem.text if symbol_elem is not None else 'error'
    next_state = state_dico[next_state_txt]
    is_defined = symbol_elem is not None
    if is_defined and 'push' in symbol_elem.attrib.keys():
        return 'U({}, {}), '.format(next_state, stack_state_dico[symbol_elem.attrib['push']])
    elif is_defined and 'pop' in symbol_elem.attrib.keys():
        return 'O({}), '.format(next_state)
    else:
        return 'T({}), '.format(next_state)
    '''

def create_file(table, src, dst):
    f = open(src, 'r')
    filedata = f.read()
    f.close()

    newdata = filedata.replace("/*\nHere\n*/", table)

    f = open(dst, 'w')
    f.write(newdata)
    f.close()

def main():
    xml_path = argv[1]
    template_path = argv[2]
    output_path = argv[3]
    tree = etree.parse(xml_path)
    root = tree.getroot()
    table = root.find('table')

    char_table = list_from_tree(root.find('char_types'))
    state_table = list_from_tree(root.find('state_types'))
    stack_table = list_from_tree(root.find('stack_types'))

    state_dico = dict((e, i) for i, e in enumerate(state_table))
    stack_dico = dict((e, i) for i, e in enumerate(stack_table))

    table_text = 'static const t_transition g_transition_table[][{}][{}] =\n{{\n'.format(len(stack_table), len(char_table))
    for state in state_table:
        state_tree = table.find(state)
        table_text += '\t{\n'
        for stack in stack_table:
            stack_tree = state_tree.find(stack) if state_tree != None else None
            table_text += '\t\t{'
            for symbol in char_table:
                table_text += print_transition(symbol, stack_tree, state_dico, stack_dico)
            table_text += '},\n'
        table_text += '\t},\n'
    table_text += '};'
    create_file(table_text, template_path, output_path)

if __name__ == "__main__":
    main()
