
;---------------------------------------------------------------------------
;  config.clp - CLIPS agent configuration tools
;
;  Created: Wed Dec 19 20:45:53 2012 (Train from Munich to Freiburg)
;  Copyright  2012  Tim Niemueller [www.niemueller.de]
;  Licensed under GPLv2+ license, cf. LICENSE file
;---------------------------------------------------------------------------

(deftemplate confval
  (slot path (type STRING))
  (slot type (type SYMBOL) (allowed-values FLOAT UINT INT BOOL STRING))
  (slot value)
  (slot is-list (type SYMBOL) (allowed-values TRUE FALSE) (default FALSE))
  (multislot list-value)
)

(defrule config-print-disabled-slide-counter-checks
	(machine (name ?n) (mtype RS))
	(confval (path ?p&:(eq ?p (str-cat"/llsfrb/mps/stations/" ?n "/connection")))
	         (type STRING) (is-list FALSE) (value "mockup"))
	(not (disabled-slide-printed ?n))
	=>
  (printout warn "Slide counter check for "
                 ?n " disabled, as it is using mockup mode" crlf)
	(assert (disabled-slide-printed ?n))
)

;(defrule print-confval
;  (confval (path ?p) (type ?t) (value ?v) (is-list ?is-list) (list-value $?lv))
;  =>
;  (if (debug 2) then
;    (printout t "confval path: " ?p "  type: " ?t
;	      "  value: " (if (eq ?is-list TRUE) then ?lv else ?v) crlf))
;)
