#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "input.h"
#include "queue.h"
#include "types.h"

/** List of all the node creation functions.  This is a chain of
    responsibility; we can keep trying these functions until we find
    one that knows how to parse the init string. */
static Node *(*nodeMakers[])( char const *init ) = {
  makeIntNode,
  makeRealNode,
  makeStringNode
};
