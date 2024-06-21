
/***************************************************************************
 *  machine.h - LLSF RefBox shell - Machine
 *
 *  Created: Thu Feb 21 18:02:53 2013
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

#ifndef __LLSF_REFBOX_SHELL_MACHINE_H_
#define __LLSF_REFBOX_SHELL_MACHINE_H_

#include <msgs/MachineInfo.pb.h>
#include <msgs/ProductColor.pb.h>

#include <cstddef>
#include <cursesp.h>
#include <map>
#include <memory>
#include <vector>

namespace llsfrb_shell {
#if 0 /* just to make Emacs auto-indent happy */
}
#endif

class LLSFRefBoxShellMachine : public NCursesPanel
{
public:
	LLSFRefBoxShellMachine(std::string name,
	                       std::string type,
	                       int         begin_y,
	                       int         begin_x,
	                       bool        visible = true);
	~LLSFRefBoxShellMachine();

	void update(const llsf_msgs::Machine &minfo);

	void flip_blink_states();
	void set_visible(bool visible);

	void reset();

	int refresh();

private:
	bool                                                   visible_;
	std::shared_ptr<llsf_msgs::Machine>                    minfo_;
	std::map<llsf_msgs::LightColor, llsf_msgs::LightState> lights_;
	std::map<llsf_msgs::LightColor, bool>                  blink_state_;
};

} // namespace llsfrb_shell

#endif
