/**
 * Author: Arman Ferdous
 * Date: 2019-12-28
 * License: CC0
 * Source: Internet
 * Description: Set block size $B = (2n^2)^{1/3}$. Sort queries by $(\lfloor \frac{L}{B} \rfloor, \lfloor \frac{R}{B} \rfloor, t)$, where $t = $ number of updates before this query. Then process queries in sorted order, modify $L, R$ and then apply/undo the updates to answer. 
 * Time: $O(Bq + qn^2/B^2)$ or $O(qn^{2/3})$ with that B.
 */

