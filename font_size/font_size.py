def line_occupy(width, font_size, x):  # x: n characters
    one_line_len = width/font_size
    if x % one_line_len == 0:
        n_lines = x/one_line_len
    else:
        n_lines = x/one_line_len + 1
    return n_lines


def create_line_list(width, font_size, char_list):
    line_list = []
    for num in char_list:
        line_list.append(line_occupy(width, font_size, num))
    return line_list


def sat(char_list, n_pages, height, width, font_size):
    if width < font_size:
        return False
    n_line_limit = n_pages*height/font_size
    n_line_list = create_line_list(width, font_size, char_list)
    n_line_require = sum(n_line_list)
    return n_line_limit >= n_line_require


def search_in(start, end, char_list, n_pages, height, width):
    if end - start <= 10:
        for i in range(end, start - 1, -1):
            if sat(char_list, n_pages, height, width, i):
                return i
    else:
        if sat(char_list, n_pages, height, width, (start + end)/2):
            return search_in((start + end)/2, end, char_list, n_pages, height, width)
        else:
            return search_in(start, (start + end)/2 - 1, char_list, n_pages, height, width)


def main():
    n_samples = int(raw_input())
    while n_samples > 0:
        n_samples -= 1

        useless, n_pages, width, height = map(int, raw_input().split(' '))
        chars_list = map(int, raw_input().split(' '))
        fs = 1
        while sat(chars_list, n_pages, height, width, fs):
            fs *= 2
        if fs == 1:
            print 1
        else:
            print search_in(fs/2, fs, chars_list, n_pages, height, width)


if __name__ == '__main__':
    main()

