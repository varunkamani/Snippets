int lps[100000];
void CreateLPS(string word) {
    int l = word.length();
    int len = 0;
    int i = 1;
    while(i < l) {
        if(word[i] == word[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len == 0) {
                i++;
            } else {
                len = lps[len - 1];
            }
        }
    }
}
int FindWord(string text, string word) {
    int i = 0, j = 0;
    int l1 = text.length(), l2 = word.length();
    while(i < l1 && j < l2) {
        if(text[i] == word[j]) {
            i++;
            j++;
            if(j == l2) return i - j;
        } else {
        	if(j == 0) i++;
        	else j = lps[j-1];
        }
    }
    return -1;
}
