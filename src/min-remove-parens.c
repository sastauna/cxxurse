unsigned char *minRemoveToMakeValid(unsigned char *s) {
	unsigned write_index = 0;
	{
		unsigned count   = 0;
		unsigned removed = 0;
		unsigned char c;
		do {
			c = s[write_index + removed];

			if (c == '(') {
				count++;
			} else if (c == ')') {
				if (count) {
					count--;
				} else {
					removed++;
					continue;
				}
			}

			s[write_index] = c;
			write_index++;
/*
			if (c == '\0') {
				break;
			}
		} while(1);
/*/
		} while(__builtin_expect(c != '\0', 1));
//*/
	}

	unsigned removed = 0;
	{
		unsigned count = 0;
		int read_index = write_index - 1;
		while(__builtin_expect(read_index --!= 0, 1)) {
			unsigned char c = s[read_index];

			if (c == ')') {
				count++;
			} else if (c == '(') {
				if (count) {
					count--;
				} else {
					removed++;
					continue;
				}
			}

			s[read_index + removed] = c;
		}
	}

	return s + removed;
}
