Academic Honesty
----------------

The University of Chicago has a `formal policy on academic honesty <http://college.uchicago.edu/advising/academic-integrity-student-conduct>`_
that you are expected to adhere to. In this page, we elaborate on what we understand by academic honesty,
and provide specific rules to ensure that you do not cross
the line into academic dishonesty.

Academic dishonesty can encompass many activities, but one of the gravest is plagiarism:
knowingly handing in someone else's work as your  own, whether it be work done by another
student in the class or  available publicly on the Internet. We take incidents of plagiarism
extremely seriously in this class, and will escalate any such cases to the Dean of Students
in the College for further adjudication. Going through disciplinary proceedings is an
unpleasant experience for everyone involved, and the outcome of these cases can have
an impact on your grade, up to the possibility of failing the course outright.

Please note that plagiarism is fairly easy for us to detect: we use a
series of automated tools that look for similarities between your code
and other students' code (across all sections of the class), including
code submitted in previous offerings of this class (or other similar
classes). Any similarities flagged by these tools are then manually
checked by an instructor so, if you use someone else's code (even if
you edit the code so it's not a verbatim copy), it is very likely you
will get caught.

Fortunately, you can avoid plagiarism by following these guidelines!

Never do any of the following:

- **Ask another student in the class if you can see their code.** It doesn't matter how you want to use it: even if you just want to skim through their solution for inspiration, this is still plagiarism.

- **Show or share your code with another student in the class.** If someone in the class asks you to share your code with them, even if you're certain they won't use it and they just want to look at it to get "unstuck", please point them to this page. If you willingly share your code with someone else, you are an equally guilty party in a plagiarism offense.

- **Post your code in publicly-accessible websites**, e.g., pastebin, a public GitHub repository, GitHub gists, etc. While it can be a convenient mechanism to share code with an instructor/TA, it can also expose your code to other students in the class. You are provided with a private repository on GitHub, and you should use that repository exclusively to do your work in this class.

*Please note that these prohibitions also apply after the course is over!* You should never share your code from this class with other people, either during the course itself or at any time in the future.

We make only one exception to this rule: if a prospective employer asks to see samples of your code, you are welcome to send them your code from this class, but must do so privately, not by posting your code in a publicly-accessible location.

All that said, we do encourage a collaborative environment in this class, as long as it doesn’t slip into the realm of plagiarism. Make sure you are careful about the following:

- **Using code you find on the Internet.** There are certain situations where consulting and citing online sources (including those that may show code examples) is appropriate. However, please be aware that, the moment you use code on the Internet, you risk your work getting flagged as plagiarism.  (See below for more information about citing outside sources.)

- **Discussing the projects with students other than your project partner**. You should not share or write code together with other students (except your project partner). Any discussions you have with other students should focus on high-level aspects of the projects (e.g. "Can you explain what this task is asking me to do?"). You should not discuss implementation details, except at a high level, since this can result in students submitting nearly identical work.

- **"Whiteboarding" (discussing an assignment with other students by sketching out code on a whiteboard).** This may cross the line into academic dishonesty (even when using pseudocode).  In any such discussions, you should focus on using the discussion as a way to understand the high-level aspects of the problem, and then *write your own code from scratch*.  Do not sketch out detailed solutions to the problem on a whiteboard.  Do not write detailed notes during the discussion or take photographs of the whiteboard.   Finally, we encourage you to take a break between a whiteboard discussion and writing your own code.

By themselves, the above won't necessarily cross the line into plagiarism, but you may still receive a stern warning if we believe you are getting close to crossing the line.


Citing your sources
~~~~~~~~~~~~~~~~~~~

If you relied on any external sources, you must include proper citations in a ``README`` file in your repository. Alternatively, if your use of an external source pertains to a specific portion of your code, including a code comment above that code (stating that you consulted an external source when writing that piece of code) is also acceptable.

You should be particularly careful about the following:

- **If you have discussed parts of an assignment with someone else**, then make sure to say so in the ``README`` file.

- **If you use outside resources**: you *must* cite the source you used; you *must not* use verbatim blocks of code from that source; and you *must not* rely on sources that provide a complete (or nearly complete) solution to the assignment.

- **If you rely on small code examples that are used to illustrate a concept**, never use those examples verbatim in your code. We understand that, in some cases, your own code may be reasonably similar to those examples (e.g., because there are very few ways in which a given piece of code could be written). To ensure this is not flagged as plagiarism, always err on the side of including a citation.

Using third-party libraries
~~~~~~~~~~~~~~~~~~~~~~~~~~~

The use of external libraries is generally allowed on all
the projects, as long as they don't provide networks-related functionality
that you're expected to implement. If you want to be on the safe side,
you can ask us whether given library is ok to use. Please note
that the following libraries are pre-approved, and you are welcome to use them
in your projects (in fact, many students have used them in past years):

- `utlist <https://troydhanson.github.io/uthash/utlist.html>`_: A linked list library
- `uthash <https://troydhanson.github.io/uthash/>`_: A hash table for C structures
- `SDS <https://github.com/antirez/sds>`_: Simple Dynamic Strings


Policy on Generative AI
~~~~~~~~~~~~~~~~~~~~~~~

When using Generative AI systems (GenAI), it is important that you use them in a way that **supplements** your learning, instead of **substituting** your learning. Yes, you may have heard how software developers use GenAI as part of their workflow, but you are not yet a software developer! You are still at a stage in your learning where it is important that you complete programming tasks by yourself, so you can build a strong foundation in programming.

Please trust that, if we ask you to perform a task by yourself, it is because it will benefit your learning (and that taking shortcuts on that task will not prepare you well for further CS studies). Programming is a skill, and the way you will get better at it is by practicing that skill. Asking GenAI to solve programming tasks for you is like trying to learn how to play the piano by asking someone to play the piano for you. You may get the gist of what is involved, but you won't be able to do it yourself.

As such, you **must not** use Generative AI systems (GenAI), such as ChatGPT or GitHub Copilot, to write or generate any of your code in this class.

You may use these systems **for reference purposes only**, but you must tread very carefully:

- For academic honesty purposes, you must treat these systems like any other external resources (similar to looking something up on Wikipedia, Stack Overflow, etc.). This means you must always provide citations when using GenAI, including the exact prompt you used and, if supported, a link to the chat conversation (for ChatGPT, see the `ChatGPT Shared Links FAQ <https://help.openai.com/en/articles/7925741-chatgpt-shared-links-faq>`__)
- When using GenAI, don’t forget that these systems **have no sense of what is true or not**, and will sometimes provide incorrect answers. Additionally, even when providing correct answers, those answers may contradict instructions/guidance we provide in this class. It is important that you **always** look at answers from GenAI with a critical eye, and that you remember that the content we provide in the class always takes precedence.
- In general, you must only use them to answer specific conceptual questions, and never to request that the system generate any code for you. For example, it would be appropriate to ask GenAI the following: "Is there a function in C to split a string based on a separator?". It would also be appropriate to use GenAI to deepen your understanding of topics we've covered in class. For example: "Can you give me an overview of the latest research in TCP Congestion Control?"
- If you are concerned about academic honesty issues, a good heuristic to use in order to figure out what is or isn’t appropriate is to imagine GenAI as a **helpful but fallible classmate**. For example, it is generally appropriate to review lecture notes with a classmate and ask questions about concepts you didn’t fully understand. So, asking GenAI about this is likely fine. On the other hand, it is never fine to ask a classmate to write part or all of a homework for you.

What to do when you feel desperate?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We realize that sometimes students commit plagiarism out of desperation
and as a measure of last resort. If you are in this situation, please
just ask the instructors or other course staff for help. If you are having a hard time in the
class, we will provide as much assistance as we can. Plus, a poor performance in
one assignment is unlikely to wreck your grade for the class. Plagiarism
is never worth it.

The impact of a violation on your final grade
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If you are found in violation of this policy, the effect on your grade
will be severe. At minimum, your final course grade will drop one full
step (letter). At maximum, you will receive an F in the course.
Furthermore, please note that the instructors are required to report
all infractions to the College. If you violate this policy, you may be
subject to further penalty or action by the College.

Finally, if you have any questions regarding what would or would not be considered academic dishonesty in this course, please don’t hesitate to ask your instructor.




