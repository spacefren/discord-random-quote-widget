# 💬 Discord Random Quote Widget

<img width="400" height="287" alt="image" src="https://github.com/user-attachments/assets/85ddc4b5-d3d1-41f3-a411-c7e66ec33177" />
<img width="400" height="287" alt="image" src="https://github.com/user-attachments/assets/edfb0dd6-1096-43d7-aa0d-7b170ed0089b" />

<br> Display a quote in your discord profile and automatically update it in a given interval.

## Setup

#### 1. Fork this repository

#### 2. Create a discord application and widget
Follow the steps in ![this blog post](https://chloecinders.com/blog/discord-widgets) by chloecinders. Alternatively, use the ![automated script](https://gist.github.com/aamiaa/7cdd590e3949cd654758bc90bcb4710b) by aamiaa.

#### 3. Adjust the widget data fields
Edit the widget and fill in all the required fields (see the `Validation` tab). For each of the following sections, select `UserData` under Value Type and set the following data fields:
|Field|Presentation Type|Data Field|
|---|---|---|
|Widget Top → Image|---|`quote-image`|
|Widget Top → Title|Text|`quote-text-1`|
|Widget Top → Subtitle 1|Text|`quote-text-2`|
|Widget Top → Subtitle 3|Text|`quote-author`|
|Widget Bottom → Objective|---|`image-credit-text`|
|Widget Bottom → Progress → Current Value|---|`quote-number`|
|Widget Bottom → Progress → Max Value|---|`quote-count`|

For the Widget Bottom fields to show up, set the design type to `Progress`.

> [!TIP]
> You can populate the data with placeholders under the `Sample Data` tab by assigning each of the data fields a value.

> [!TIP]
> `Subtitle 2` remains unused. By selecting `Custom String`, you can add any static text. Consider using an invisible, non-whitespace unicode character (such as the zero width joiner) to create some spacing between the quote and the author.

#### 4. Add github secrets
In your github fork, go to **Settings** → **Secrets and variables** → **Actions** → **New repository secret** and add the following data from your discord application dashboard:
|Secret|Value|
|---|---|
|`APP_ID`|Your discord app's ID (General Information → Application ID)
|`BOT_TOKEN`|Your discord bot's token (Bot → Token, reset if needed)
|`USER_ID`|Your discord user ID. Find it in the app using developer mode or find a guide.

#### 5. Change the quotes
Modify the `Resources/quotes.json` file.
- To create a quote that spans two lines (title and subtitle), separate with `\n`.
- For images, make sure the link resolves to an image.

> [!TIP]
> When using the `Hero` version of the widget, the image will be slightly bigger than the container. Consider using a transparent image to make the character pop out, or add a transparent band at the top.

#### 6. Run it
Open **Actions** → **Update quote** → **Run workflow**. Upon the first successfull run, the quote will change every day (modify the cron schedule at `.github/workflows/main.yml` to change the interval).
