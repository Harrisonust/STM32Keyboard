#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

/** 
 * @brief everything needs to be drawn once should be called here
 */
void display_manager_init();

/** 
 * @brief every ssd_draw functoin should only be called in this function 
 *        after that, ssd_update function will be called once, all the previous
 *        draws should be then updated.
 */
void display_manager_update();

#endif