
/***************************************************************************
 *  order.h - LLSF RefBox shell - Order
 *
 *  Created: Mon Feb 25 11:45:22 2013
 *  Copyright  2013  Tim Niemueller [www.niemueller.de]
 ****************************************************************************/

/*  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the authors nor the names of its contributors
 *   may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __LLSF_REFBOX_SHELL_ORDER_H_
#define __LLSF_REFBOX_SHELL_ORDER_H_

#include <msgs/OrderInfo.pb.h>

#include <cstddef>
#include <cursesp.h>
#include <map>
#include <vector>

namespace llsfrb_shell {
#if 0 /* just to make Emacs auto-indent happy */
}
#endif

class LLSFRefBoxShellOrder : public NCursesPanel
{
public:
	LLSFRefBoxShellOrder(int begin_y, int begin_x);
	~LLSFRefBoxShellOrder();

	void update(unsigned int                       id,
	            llsf_msgs::Order::Complexity       complexity,
	            bool                               competitive,
	            llsf_msgs::BaseColor               base_color,
	            std::vector<llsf_msgs::RingColor> &ring_colors,
	            llsf_msgs::CapColor                cap_color,
	            unsigned int                       quantity_requested,
	            unsigned int                       quantity_delivered_cyan,
	            unsigned int                       quantity_delivered_magenta,
	            unsigned int                       delivery_period_begin,
	            unsigned int                       delivery_period_end,
	            unsigned int                       delivery_gate);
	void set_gametime(unsigned int game_time);

	void reset();

	int refresh();

private:
	unsigned int                      id_;
	llsf_msgs::Order::Complexity      complexity_;
	bool                              competitive_;
	llsf_msgs::BaseColor              base_color_;
	std::vector<llsf_msgs::RingColor> ring_colors_;
	llsf_msgs::CapColor               cap_color_;
	unsigned int                      quantity_requested_;
	unsigned int                      quantity_delivered_cyan_;
	unsigned int                      quantity_delivered_magenta_;
	unsigned int                      delivery_period_begin_;
	unsigned int                      delivery_period_end_;
	unsigned int                      delivery_gate_;

	unsigned int game_time_;
};

} // namespace llsfrb_shell

#endif
