/**
 * Author: User
 * Date: 2024
 * License: CC0
 * Source: User-provided
 * Description: Rotate a matrix by 90 degrees clockwise.
 * Usage: See examples below
 * Time: O(n*n) for an n x n matrix
 */
#pragma once

ans[j][n + 1 - i] = v[i][j];
ans[n + 1 - i][n + 1 - j] = v[j][n + 1 - i];
ans[n + 1 - j][i] = v[n + 1 - i][n + 1 - j];
ans[i][j] = v[n + 1 - j][i];